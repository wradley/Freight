#pragma once

namespace fr
{
    template <class T, class E>
    class Result
    {
        inline Result() {}

    public:

        inline ~Result() {}

        inline static Result Ok(const T &t) {
            Result r;
            r.mOk = true;
            r.mData = t;
            return r;
        }

        inline static Result Err(const E &err) {
            Result r;
            r.mOk = false;
            r.mErr = err;
            return r;
        }

        inline bool ok() const {
            return mOk;
        }

        inline T& get() {
            FR_ASSERT(mOk, "Result is not okay.");
            return mData;
        }

        inline E& err() {
            FR_ASSERT(!mOk, "Result is okay.");
            return mErr;
        }


    private:

        bool mOk;
        union {
            T mData;
            E mErr;
        };
    };
}