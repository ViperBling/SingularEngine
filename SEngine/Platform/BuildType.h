#pragma once

#if defined(_SEDebug_)
#define SINGULAR_BUILD_DEBUG
#elif defined(_SERelease_)
#define SINGULAR_BUILD_RELEASE
#endif