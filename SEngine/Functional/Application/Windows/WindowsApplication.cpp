#include "WindowsApplication.h"

#include "Platform/Assert.h"
#include "Core/Math/MathPCH.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/GUI/GUIManager.h"
#include "Functional/Scene/SceneManager.h"
#include "Resource/AssetManager/AssetLoader.h"

using namespace SingularEngine;


void WindowsApplication::Initialize(std::shared_ptr<ApplicationInitParams> param) {
    Application::Initialize(param);
}

void WindowsApplication::Finalize() {

}

void WindowsApplication::Tick() {

}

HWND WindowsApplication::GetWindowHandler() noexcept {
    return nullptr;
}

void WindowsApplication::SetWindowTitle(std::string &title) {

}

void WindowsApplication::SetupApplicationTitle(std::shared_ptr<ApplicationInitParams> param) {

}

void WindowsApplication::OnWindowSizeChange(int width, int height) {

}

LRESULT WindowsApplication::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
    return 0;
}

LRESULT WindowsApplication::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
    return 0;
}

LRESULT WindowsApplication::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
    return 0;
}

void WindowsApplication::InitMainWindow(int width, int height) {

}

void WindowsApplication::InitRenderer(RenderAPI api, int width, int height) {

}
