#pragma once

#include "Platform/Platform.h"
#include "Functional/Application/Application.h"

#ifdef SINGULAR_PLATFORM_WINDOWS

namespace SingularEngine
{
    class WindowsApplication : public Application
    {
    public:
        void Initialize(std::shared_ptr<ApplicationInitParams> param) override;
        void Finalize() override;
        void Tick() override;

        HWND GetWindowHandler() noexcept;
        void SetWindowTitle(std::string& title);
        void SetupApplicationTitle(std::shared_ptr<ApplicationInitParams> param);

    protected:
        virtual void OnWindowSizeChange(int width, int height);

    private:
        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

        void InitMainWindow(int width, int height);
        void InitRenderer(RenderAPI api, int width, int height);

    private:
        HWND mHWND{};
    };
}

#endif