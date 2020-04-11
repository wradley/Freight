#include <vector>
#include "TestStage.hpp"

namespace fr::Test
{
    class TestResult
    {
    public:

        TestResult(const std::string &name) : mName(name), mStages() {}
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
        }

        inline bool passed() const {
            for (auto &stage : mStages) {
                if (stage.passed() == false)
                    return false;
            }
            return true;
        }

        inline std::string toString() const {
            std::string ret(mName);
            ret.append(": ");
            passed() ? ret.append("Passed") : ret.append("Failed");

            if (mStages.size() == 1 && mStages[0].name() == "")
                return ret;
            else 
                ret.append("\n");

            for (size_t i = 0; i < mStages.size(); ++i) {
                ret.append("  ");
                ret.append(mStages[i].toString());
                if (i < mStages.size() - 1)
                    ret.append("\n");
            }
            return ret;
        }

    private:

        std::string mName;
        std::vector<TestStage> mStages;

    };
}