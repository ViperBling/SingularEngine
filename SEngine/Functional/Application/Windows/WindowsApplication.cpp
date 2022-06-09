#include "WindowsApplication.h"

#ifdef SINGULAR_PLATFORM_WINDOWS

#include "Platform/Assert.h"
#include "Core/Math/MathPCH.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/RHI/D3D11/RendererD3D11.h"
#include "Functional/GUI/GUIManager.h"
#include "Functional/Scene/SceneManager.h"
#include "Resource/AssetManager/AssetLoader.h"
#include "Functional/Scene/RenderPass/RenderPassManager.h"

using namespace SingularEngine;


void WindowsApplication::Initialize(std::shared_ptr<ApplicationInitParams> param) {
    Application::Initialize(param);
    InitMainWindow(param->WindowWidth, param->WindowHeight);
    InitRenderer(param->RenderAPIType, param->WindowWidth, param->WindowHeight);


    if (param->EditorMode) {
        GUIManager::Initialize(true, true);
    }
    else {
        GUIManager::Initialize(false, false);
    }
    SetupApplicationTitle(param);
}

void WindowsApplication::Finalize() {

    GUIManager::Finalize();

    SceneManager::Instance->Finalize();
    delete SceneManager::Instance;
    SceneManager::Instance = nullptr;

    delete RenderPassManager::Instance;
    RenderPassManager::Instance = nullptr;

    Renderer::Instance->Finalize();
    delete Renderer::Instance;
    Renderer::Instance = nullptr;
}

void WindowsApplication::Tick() {

    MSG msg{};
    while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HWND WindowsApplication::GetWindowHandler() noexcept {

    return mHWND;
}

void WindowsApplication::SetWindowTitle(std::string &title) {

    SetWindowText(mHWND, title.c_str());
}

void WindowsApplication::SetupApplicationTitle(std::shared_ptr<ApplicationInitParams> param) {

    std::string title;
    std::string mode;
    std::string render;

    if (param->EditorMode) {
        mode = "Editor";
    }
    else {
        mode = "Runtime";
    }
    if (param->RenderAPIType == RenderAPI::D3D11) {
        render = "D3D11";
    }
    else {
        render = "OpenGL";
    }
    sprintf(title.data(), "Engine - [mode: %s] - [render: %s]", mode.c_str(), render.c_str());
    SetWindowTitle(title);
}

void WindowsApplication::OnWindowSizeChange(int width, int height) {

    if (Renderer::Instance != nullptr) {
        Renderer::Instance->ResizeResolution(width, height);
        if (!mConfig->EditorMode) {
            RenderPassManager::Instance->ResizeResolution(width, height);
        }
    }
}

LRESULT WindowsApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    if (GUIManager::HandleEvents(hWnd, message, wParam, lParam))
    {
        return true;
    }


    auto app = reinterpret_cast<WindowsApplication*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    switch (message)
    {
        case WM_CREATE:
        {
            auto pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
            break;
        }
        case WM_DESTROY:
        {
            app->mbQuit = true;
            break;
        }
        case WM_SIZE:
        {
            if (wParam != SIZE_MINIMIZED)
            {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                app->OnWindowSizeChange((int)width, (int)height);
            }
            break;
        }
        case WM_DPICHANGED:
        {
            GUIManager::HandleMultiViewport(hWnd, lParam);
            break;
        }
        default:
            break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void WindowsApplication::InitMainWindow(int width, int height) {

    HINSTANCE hInstance = GetModuleHandle(nullptr);
    WNDCLASSEX windowClass{};
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.lpszClassName = "Singular Engine";
    RegisterClassEx(&windowClass);

    RECT windowRect = { 0, 0, width, height };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    // Create the window and store a handle to it.
    mHWND = CreateWindowEx(
        NULL,
        windowClass.lpszClassName,
        "Singular Engine",
        WS_OVERLAPPEDWINDOW,
        100,
        100,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr,        // We have no parent window.
        nullptr,        // We aren't using menus.
        hInstance,
        this);

    // Initialize the sample. OnInit is defined in each child-implementation of DXSample.
    ShowWindow(mHWND, 5);
}

void WindowsApplication::InitRenderer(RenderAPI api, int width, int height) {

    SINGULAR_ASSERT(Renderer::Instance == nullptr);
    if (api == RenderAPI::D3D11)
    {
        Renderer::Instance = new RendererD3D11();
    }
    else if (api == RenderAPI::OpenGL)
    {
//        Renderer::Instance = new OpenglRenderer();
    }
    else
    {
        SINGULAR_ASSERT(false);
    }

    CreateRendererContextParam param{};
    param.mHWND = mHWND;
    param.mResolutionWidth = width;
    param.mResolutionHeight = height;
    Renderer::Instance->Initialize(param);
    Renderer::Instance->SetViewPort(0, 0, width, height);

    RenderPassManager::Instance = new RenderPassManager();
    RenderPassManager::Instance->Init(param);
}

#endif