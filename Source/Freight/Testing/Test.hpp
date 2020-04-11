#include <functional>
#include <vector>
#include <iostream>
#include "TestResult.hpp"
#include "TestUtil.hpp"


namespace fr::Test
{
    using TestFn = std::function<void(TestResult &)>;

    struct NameTestPair
    {
        std::string name;
        fr::Test::TestFn test;

        inline int operator+ (fr::Test::TestFn fn) 
        {
            test = fn;
            return 0;
        }
    };

    NameTestPair& RegisterFn(const std::string &name);

    struct TestResults
    {
        void operator += (TestFn fn);
    };
}

#define _UNIQUE_NAME(a, b) a ## b
#define _UNIQUE_NAME2(a, b) _UNIQUE_NAME(a, b)

// static int unique_name = RegisterFn(name, [](TestResult&)
#define FR_TEST(name) static int _UNIQUE_NAME2(test_fn_, __LINE__) = fr::Test::RegisterFn(fr::Test::FormatFileLineName(__FILE__, __LINE__, name)) + [](fr::Test::TestResult &_TEST_RESULT)
#define FR_STAGE(name) _TEST_RESULT.newStage(fr::Test::FormatLineName(__LINE__, name));
#define FR_REQUIRE(pass) _TEST_RESULT.stageResult(pass);

#ifdef FR_ENABLE_TESTING

static std::vector<fr::Test::NameTestPair*> sTests;

namespace fr::Test
{
    fr::Test::NameTestPair& RegisterFn(const std::string &name) {
        auto pair = new fr::Test::NameTestPair;
        pair->name = name;
        sTests.push_back(pair);
        return *pair;
    }
}

int main() {
    std::string totalTestString = sTests.size() > 1 ? " Tests" : " Test";
    std::cout << "\nRunning " << sTests.size() << totalTestString << std::endl;
    unsigned int passed = 0, total = 0;
    for (auto pair : sTests) {
        fr::Test::TestResult result(pair->name);
        pair->test(result);
        std::cout << "\n" << result.toString() << std::endl;
        ++total;
        if (result.passed()) ++passed;
    }
    std::cout << "\nPassed " << passed << "/" << total << " tests.\n" << std::endl;
    return 0;
}

#endif