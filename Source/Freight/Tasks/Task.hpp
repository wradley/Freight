#pragma once
#include <atomic>
#include <thread>
#include <memory>
#include <vector>
#include <deque>
#include <mutex>
#include <functional>
#include "../String.hpp"

namespace fr
{
    class Task
    {
    public:
        
        Task();
        virtual ~Task();
        
        virtual void run() = 0;
        
        // override for custom completion handler such as
        // incrementing an atomic counter for multiple tasks
        virtual void onComplete();
        
        void markComplete();
        bool isComplete() const;
        
    private:
        
        std::atomic_bool mFinished;
        
    };
    
    
    class TaskQueue
    {
    public:
        
        TaskQueue();
        ~TaskQueue();
        
        void push(std::shared_ptr<Task> t);
        std::shared_ptr<Task> pop();
        
    private:
        
        std::mutex mMutex;
        std::deque<std::shared_ptr<Task>> mTasks;
    };
    
    
    class TaskThread
    {
    public:
        
        TaskThread(std::shared_ptr<TaskQueue> q);
        ~TaskThread();
        
        void stop();
        void waitUntilFinished();
        bool hasStarted() const;
        bool isFinished() const;

        void setDebugname(const fr::String &name);
        
    private:
        
        friend void TaskThreadMain(TaskThread *t);
        
        std::shared_ptr<TaskQueue> mQueue;
        std::atomic_bool mStarted;
        std::atomic_bool mRunning;
        std::atomic_bool mFinished;
        std::unique_ptr<std::thread> mThread;

        fr::String mDebugName;
        
    };
    
    
    class TaskManager
    {
    public:
        
        TaskManager(size_t threadCount);
        ~TaskManager();
        
        bool allThreadsStarted() const;
//        void setThreadCount(size_t count);
        size_t getThreadCount() const;
        
        void wait(std::function<bool()>condition);
        void queue(std::shared_ptr<Task> task);
        
    private:
        
        std::shared_ptr<TaskQueue> mTaskQueue;
        std::vector<std::unique_ptr<TaskThread>> mThreads;
        
    };
}
