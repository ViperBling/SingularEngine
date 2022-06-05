#pragma once

#include "Platform.h"
#include "BuildType.h"

#if defined(SINGULAR_PLATFORM_WINDOWS)
#include <crtdbg.h>
#define SINGULAR_ASSERT_IMPL(EXPR) _ASSERTE(EXPR)
#elif defined(SINGULAR_PLATFORM_MACOS)
#include <assert.h>
#define SINGULAR_ASSERT_IMPL(EXPR) assert(EXPR)
#endif

#if defined(SINGULAR_BUILD_DEBUG)
#define SINGULAR_ASSERT(EXPR) SINGULAR_ASSERT_IMPL(EXPR)
#elif defined(SINGULAR_BUILD_RELEASE)
#define SINGULAR_ASSERT(EXPR) ((void)0)
#endif