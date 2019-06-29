#include "Task.hpp"

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
        while (t->mRunning.load()) {
            auto task = t->mQueue.pop();
            if (task.get()) {
                task->run();
                task->markFinished();
                task->onComplete();
            }
        }
        
        t->mFinished.store(true);
    }
    
    TaskThread::TaskThread(TaskQueue &q) :
        mQueue(q),
        mRunning(true),
        mFinished(false),
        mThread(nullptr)
    {
        mThread = std::unique_ptr<std::thread>(new std::thread(TaskThreadMain, this));
        mThread->detach();
    }
    
    
    TaskThread::~TaskThread()
    {}
    
    
    void TaskThread::stop()
    {
        mRunning.store(false);
    }
    
    
    void TaskThread::waitUntilFinished()
    {
        mThread->join();
    }
    
    
    bool TaskThread::isFinished() const
    {
        return mFinished.load();
    }
    
    
    // Task Manager ---------------------------------
    
    
    TaskManager::TaskManager(size_t threadCount)
    {
        mThreads.reserve(threadCount);
        
        for (size_t i = 0; i < threadCount; ++i) {
            mThreads.push_back(std::make_unique<TaskThread>(mTaskQueue));
        }
    }
    
    
    TaskManager::~TaskManager()
    {
        for (auto &thread : mThreads)
            thread->stop();
        
        for (auto &thread : mThreads)
            thread->waitUntilFinished();
    }
    
    
    size_t TaskManager::getThreadCount() const
    {
        return mThreads.size();
    }
    
    
    void TaskManager::queue(std::shared_ptr<Task> task)
    {
        mTaskQueue.push(task);
    }
}
