#include "SandboxApp.hpp"
#include <atomic>

namespace FR8
{
    class TestTask : public Task
    {
    public:

        const int Times = 1000000;

        TestTask(std::atomic_int &data, std::atomic_int &finished) : mData(data), mFinished(finished) {}
        ~TestTask() {}

        // Inherited via Task
        virtual void run() override
        {
            for (int i = 0; i < Times; ++i) {
                ++mData;
            }
        }

        virtual void onComplete() override { 
            ++mFinished; 
        }

    private:

        std::atomic_int &mData;
        std::atomic_int &mFinished;

    };

    void SandboxApp::start()
    {
        FR8_DBG_LOG("App Start");
        Logger::Flush();
    }

    void SandboxApp::update()
    {
        //FR8_DBG_LOG("App Update: begin tasks");
        //std::atomic_int data(0);
        //std::atomic_int finished(0);
        //TaskManager tm(6);
        //int numTasks(128);

        //for (int i = 0; i < numTasks; ++i) {
        //    TestTask *task = new TestTask(data, finished);
        //    tm.queue(std::shared_ptr<Task>(task));
        //}

        ///*while (!tm.allThreadsStarted()) {
        //    FR8_DBG_LOG("Waiting for all threads to start");
        //}*/

        //tm.wait([&]() {
        //    return finished == numTasks;
        //});

        //FR8_DBG_LOG("Finished: " << data);
    }

    void SandboxApp::stop()
    {
        FR8_DBG_LOG("App Stop");
        Logger::Flush();
    }
    
    
    Freight* Freight::GetApp()
    {
        return new SandboxApp;
    }
}
