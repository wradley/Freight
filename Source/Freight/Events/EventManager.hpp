#pragma once
#include <memory>
#include <functional>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <atomic>

namespace fr
{
    template <class Evnt>
    using EventHandler = std::function<void(std::shared_ptr<const Evnt>)>;
    using HandlerMask = unsigned long long int;

    class EventManager
    {
        class EventHandlerListBase
        {
        public:
            inline virtual ~EventHandlerListBase() {}
        };

        template <class Evnt>
        class EventHandlerList : public EventHandlerListBase
        {
        public:
            virtual ~EventHandlerList() {}
            std::vector<std::tuple<HandlerMask, EventHandler<Evnt>>> handlers;
        };

    public:

        static inline EventManager& Instance()
        {
            static EventManager inst;
            return inst;
        }


        inline HandlerMask GenMask()
        {
            return mNextMask++;
        }


        template <class Evnt>
        void on(EventHandler<Evnt> handler, HandlerMask mask = 0)
        {
            getHandlerList<Evnt>().handlers.push_back(std::make_tuple(mask, handler));
        }
        
        template <class Evnt>
        void post(std::shared_ptr<const Evnt> e, HandlerMask mask = 0)
        {
            for (std::tuple<HandlerMask, EventHandler<Evnt>> &tuple : getHandlerList<Evnt>().handlers) {
                HandlerMask &handlerMask = std::get<0>(tuple);
                EventHandler<Evnt> &handler = std::get<1>(tuple);
                if (handlerMask != mask || handlerMask == 0 || mask == 0) {
                    handler(e);
                }
            }
        }

    private:

        EventManager() : mHandlerMap(), mNextMask(1) {}
        ~EventManager() {}

        template <class Evnt>
        EventHandlerList<Evnt>& getHandlerList()
        {
            auto ti = std::type_index(typeid(Evnt));

            // if there is no mapping for this type, create one
            if (mHandlerMap.find(ti) == mHandlerMap.end()) {
                mHandlerMap[ti] = std::unique_ptr<EventHandlerListBase>(new EventHandlerList<Evnt>);
            }

            EventHandlerListBase *list = mHandlerMap[ti].get();
            return *(static_cast<EventHandlerList<Evnt> *>(list));
        }

    private:

        std::unordered_map<std::type_index, std::unique_ptr<EventHandlerListBase>> mHandlerMap;
        std::atomic<HandlerMask> mNextMask;

    };
}