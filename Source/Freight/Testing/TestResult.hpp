#include <vector>
#include "TestStage.hpp"

namespace fr::Test
{
    class TestResult
    {
    public:

        TestResult(const std::string &name) : mPassed(true), mName(name), mStages() {}
        ~TestResult() {}

        inline void newStage(const std::string &name) {
            mStages.push_back(TestStage(name));
        }

        // set newest stage to pass or fail
        inline void stageResult(bool passed) {
            if (mStages.size() == 0) {
                mStages.push_back(TestStage(""));
            }
            mStages.back().setResult(passed);
            if (!passed) mPassed = false;
        }

        inline bool passed() const {
            return mPassed;
        }

        inline std::string toString(bool showOnlyFailed = false) const {
            if (showOnlyFailed && passed()) return "";

            std::string ret(mName);
            ret.append(": ");
            passed() ? ret.append("Passed") : ret.append("Failed");

            if (mStages.size() == 1 && mStages[0].name() == "")
                return ret;
            else 
                ret.append("\n");

            for (size_t i = 0; i < mStages.size(); ++i) {
                if (showOnlyFailed && mStages[i].passed()) continue;
                ret.append("  ");
                ret.append(mStages[i].toString());
                if (i < mStages.size() - 1)
                    ret.append("\n");
            }
            return ret;
        }

        inline std::vector<TestStage> failedStages() const {
            std::vector<TestStage> failed;
            if (passed()) return failed;
            for (auto &stage : mStages) {
                if (!stage.passed())
                    failed.push_back(stage);
            }
            return failed;
        }

        inline const std::vector<TestStage>& stages() const {
            return mStages;
        }

        inline const std::string& name() const {
            return mName;
        }

    private:

        bool mPassed;
        std::string mName;
        std::vector<TestStage> mStages;

    };
}