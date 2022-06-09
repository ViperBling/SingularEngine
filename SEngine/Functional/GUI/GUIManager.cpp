#include "GUIManager.h"

#include <memory>
#include <imgui.h>
#include <imgui_impl_opengl3.h>

#include "Functional/RHI/Renderer.h"

#ifdef SINGULAR_PLATFORM_WINDOWS
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include "Functional/RHI/D3D11/RenderContextD3D11.h"
#endif

using namespace SingularEngine;

#ifdef SINGULAR_PLATFORM_WINDOWS
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

void GUIManager::Initialize(bool docking, bool multivp) {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    if (docking) {
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    }
    if (multivp && Renderer::Instance->mAPIType == RenderAPI::D3D11) {
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    }

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

#ifdef SINGULAR_PLATFORM_WINDOWS
    ImGui_ImplWin32_Init(Renderer::Instance->mHWND);
#endif

    if (Renderer::Instance->mAPIType == RenderAPI::D3D11) {
        auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext());
        ImGui_ImplDX11_Init(context->mDevice, context->mDeviceContext);
    }
    else if (Renderer::Instance->mAPIType == RenderAPI::OpenGL) {
        ImGui_ImplOpenGL3_Init("#version 420");
    }
    else {
        SINGULAR_ASSERT(false);
    }
}

void GUIManager::Begin() {

    if (Renderer::Instance->mAPIType == RenderAPI::D3D11) {
        ImGui_ImplDX11_NewFrame();
    }
    else if (Renderer::Instance->mAPIType == RenderAPI::OpenGL) {
        ImGui_ImplOpenGL3_NewFrame();
    }
    else {
        SINGULAR_ASSERT(false);
    }

#ifdef SINGULAR_PLATFORM_WINDOWS
    ImGui_ImplWin32_NewFrame();
#endif

    ImGui::NewFrame();
}

void GUIManager::End() {

    ImGui::Render();
    Renderer::Instance->SetViewPort(0, 0, -1, -1);
    Renderer::Instance->SetRenderTarget(nullptr);
    Renderer::Instance->ClearRenderTarget(nullptr, 0.1f, 0.1f, 0.1f, 1.0f);
    Renderer::Instance->SetRasterizationState(nullptr);

    if (Renderer::Instance->GetRenderAPI() == RenderAPI::D3D11) {
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
    else if (Renderer::Instance->GetRenderAPI() == RenderAPI::OpenGL) {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    else {
        SINGULAR_ASSERT(false);
    }

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {

        auto tmpIO = ImGui::GetPlatformIO();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        if (Renderer::Instance->mAPIType == RenderAPI::OpenGL)
        {
            // auto renderer = (OpenglRenderer*)Renderer::Instance;
            // renderer->MakeCurrentContext();
        }
    }
}

void GUIManager::Finalize() {

    ImGui_ImplWin32_Shutdown();

    // Cleanup
    if (Renderer::Instance->GetRenderAPI() == RenderAPI::D3D11)
    {
        ImGui_ImplDX11_Shutdown();
    }
    else if (Renderer::Instance->GetRenderAPI() == RenderAPI::OpenGL)
    {
        ImGui_ImplOpenGL3_Shutdown();
    }
    else
    {
        SINGULAR_ASSERT(false);
    }

    ImGui::DestroyContext();
}

HRESULT GUIManager::HandleEvents(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

#ifdef SINGULAR_PLATFORM_WINDOWS
    return (HRESULT)ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
#endif
}

void GUIManager::HandleMultiViewport(HWND hwnd, LPARAM lparam) {

#ifdef SINGULAR_PLATFORM_WINDOWS
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports) {

        const RECT* suggested_rect = (RECT*)lparam;

        ::SetWindowPos(
            hwnd, nullptr,
            suggested_rect->left, suggested_rect->top,
            suggested_rect->right - suggested_rect->left,
            suggested_rect->bottom - suggested_rect->top,
            SWP_NOZORDER | SWP_NOACTIVATE);
    }
#endif
}

void GUIManager::TestGUI() {

    static float f = 0.0f;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    static bool show;
    ImGui::ShowDemoWindow(&show);
}
