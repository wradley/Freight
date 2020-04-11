#include <string>

namespace fr::Test
{
    class TestStage
    {
    public:

        TestStage(const std::string &name) : mName(name), mPassed(false) {}
        ~TestStage() {}

        inline void setResult(bool passed) {
            mPassed = passed;
        }

        inline std::string toString() const {
            std::string ret(mName);
            ret.append(": ");
            mPassed ? ret.append("Passed") : ret.append("Failed");
            return ret;
        }

        inline bool passed() const {
            return mPassed;
        }

        inline const std::string& name() const {
            return mName;
        }

    private:

        std::string mName;
        bool mPassed;
    };
}