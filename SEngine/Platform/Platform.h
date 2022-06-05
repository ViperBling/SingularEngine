#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #define SINGULAR_PLATFORM_WINDOWS
#elif defined(__APPLE__)
    #define SINGULAR_PLATFORM_MACOS
#endif

#if defined(SINGULAR_PLATFORM_WINDOWS)
    #include "PlatformWindows.h"
#elif defined(SINGULAR_PLATFORM_MACOS)
    #include "PlatformMacOS.h"
#endif

namespace SingularEngine
{
    enum class RenderAPI
    {
        None = 0,
        D3D11,
        OpenGL,
    };
}