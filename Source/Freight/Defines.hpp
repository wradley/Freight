#pragma once

//#ifdef __APPLE__
//#define WIDEN_IMPL(str) (L ## str)
//#define WIDEN(str) WIDEN_IMPL(str)
//
//#ifndef __FILEW__
//#define __FILEW__ WIDEN(__FILE__)
//#endif
//#endif

#define FR_DEBUG_BUILD

namespace fr
{
    typedef float Real;
    const Real PI = (Real)3.14159265359;

    typedef unsigned int uint;

    typedef char i8;
    typedef short i16;
    typedef int i32;
    typedef long long i64;
    typedef unsigned char u8;
    typedef unsigned short u16;
    typedef unsigned int u32;
    typedef unsigned long long u64;

    const i8  i8_MIN  = -128;
    const i8  i8_MAX  =  127;
    const i16 i16_MIN = -32768;
    const i16 i16_MAX =  32767;
    const i32 i32_MIN = -2147483648;
    const i32 i32_MAX =  2147483647;
    const i64 i64_MIN = -9223372036854775808;
    const i64 i64_MAX =  9223372036854775807;

    const u8  u8_MAX  = 255;
    const u16 u16_MAX = 65535;
    const u32 u32_MAX = 4294967295;
    const u64 u64_MAX = 18446744073709551615;

    static_assert(sizeof(i8) == 1, "i8 not expected size");
    static_assert(sizeof(i16) == 2, "i16 not expected size");
    static_assert(sizeof(i32) == 4, "i32 not expected size");
    static_assert(sizeof(i64) == 8, "i64 not expected size");
    static_assert(sizeof(u8) == 1, "u8 not expected size");
    static_assert(sizeof(u16) == 2, "u16 not expected size");
    static_assert(sizeof(u32) == 4, "u32 not expected size");
    static_assert(sizeof(u64) == 8, "u64 not expected size");

    typedef float f32;
    typedef double f64;

    static_assert(sizeof(f32) == 4, "f32 not expected size");
    static_assert(sizeof(f64) == 8, "f64 not expected size");

    typedef u64 EntID;
}