#pragma once
#include <memory>
#include <functional>
#include <vector>
#include <unordered_map>
#include <typeindex>

namespace fr
{
    template <class Evnt>
    using EventHandler = std::function<void(std::shared_ptr<const Evnt>)>;

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
            std::vector<EventHandler<Evnt>> handlers;
        };

    public:

        static inline EventManager& Instance()
        {
            static EventManager inst;
            return inst;
        }

        template <class Evnt>
        void on(EventHandler<Evnt> handler)
        {
            getHandlerList<Evnt>().handlers.push_back(handler);
        }
        
        template <class Evnt>
        void post(std::shared_ptr<const Evnt> e)
        {
            for (EventHandler<Evnt> &handler : getHandlerList<Evnt>().handlers) {
                handler(e);
            }
        }

    private:

        EventManager() {}
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

    };
}