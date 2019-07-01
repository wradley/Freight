#pragma once

#define WIDEN_IMPL(str) (L ## str)
#define WIDEN(str) WIDEN_IMPL(str)

#ifndef __FILEW__
#define __FILEW__ WIDEN(__FILE__)
#endif
