#pragma once

#include <memory>

#include "Platform/Platform.h"

namespace SingularEngine
{
    class GUIManager
    {
    public:

        static void Initialize(bool docking = false, bool mutivp = false);
        static void Begin();
        static void End();
        static void Finalize();

#ifdef SINGULAR_PLATFORM_WINDOWS
        static HRESULT HandleEvents(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
        static void HandleMultiViewport(HWND hwnd, LPARAM lparam);
#endif

    private:
        static void TestGUI();
    };
}