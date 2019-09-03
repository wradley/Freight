#include "Task.hpp"
#include "../Log/Log.hpp"

namespace FR8
{
    // Task Queue --------------------------
    
    TaskQueue::TaskQueue()
    {}
    
    
    TaskQueue::~TaskQueue()
    {}
    
    
    void TaskQueue::push(std::shared_ptr<Task> t)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mTasks.push_back(t);
    }
    
    
    std::shared_ptr<Task> TaskQueue::pop()
    {
        std::lock_guard<std::mutex> lock(mMutex);
        if (mTasks.size()) {
            std::shared_ptr<Task> task = mTasks.front();
            mTasks.pop_front();
            return task;
        } else
            return std::shared_ptr<Task>(nullptr);
    }
    
    
    // Task Thread -------------------------

    
    void TaskThreadMain(TaskThread *t)
    {
        t->mStarted = true;

        while (t->mRunning) {
            auto task = t->mQueue->pop();
            if (task) {
                //FR8_DBG_LOG("Running Thread: " << t->mDebugName);
                task->run();
                task->markComplete();
                task->onComplete();
            }
        }
        
        t->mFinished = true;
        FR8_DEBUG_LOG("Thread [" << t->mDebugName << "] Finished");
    }
    
    TaskThread::TaskThread(std::shared_ptr<TaskQueue> q) :
        mQueue(q),
        mStarted(false),
        mRunning(true),
        mFinished(false),
        mThread(nullptr)
    {
        mThread = std::make_unique<std::thread>(TaskThreadMain, this);
        //mThread->detach();
    }
    
    
    TaskThread::~TaskThread()
    {}
    
    
    void TaskThread::stop()
    {
        mRunning = false;
    }
    
    
    void TaskThread::waitUntilFinished()
    {
        mThread->join();
    }


    bool TaskThread::hasStarted() const
    {
        return mStarted;
    }
    
    
    bool TaskThread::isFinished() const
    {
        return mFinished;
    }


    void TaskThread::setDebugname(const std::wstring &name)
    {
        mDebugName = name;
    }
    
    
    // Task Manager ---------------------------------
    
    
    TaskManager::TaskManager(size_t threadCount) : 
        mTaskQueue(std::make_shared<TaskQueue>())
    {
        mThreads.reserve(threadCount);
        
        for (size_t i = 0; i < threadCount; ++i) {
            mThreads.push_back(std::make_unique<TaskThread>(mTaskQueue));
            mThreads.back()->setDebugname(std::to_wstring(i));
        }
    }
    
    
    TaskManager::~TaskManager()
    {
        for (auto &thread : mThreads)
            thread->stop();
        
        for (auto &thread : mThreads)
            thread->waitUntilFinished();
    }


    bool TaskManager::allThreadsStarted() const
    {
        for (auto &thread : mThreads) {
            if (!thread->hasStarted()) return false;
        }

        return true;
    }
    
    
    size_t TaskManager::getThreadCount() const
    {
        return mThreads.size();
    }
    

    void TaskManager::wait(std::function<bool()>condition)
    {
        while (!condition()) {
            std::shared_ptr<Task> task = mTaskQueue->pop();
            if (task) {
                task->run();
                task->markComplete();
                task->onComplete();
            }
        }
    }

    
    void TaskManager::queue(std::shared_ptr<Task> task)
    {
        mTaskQueue->push(task);
    }
}
