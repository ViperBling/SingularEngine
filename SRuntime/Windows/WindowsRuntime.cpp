#include "WindowsRuntime.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/Scene/SceneManager.h"
#include "Resource/AssetManager/AssetLoader.h"
#include "Functional/GameObject/Components/MeshRenderComponent/MeshRenderComponent.h"

using namespace SingularEngine;

void WindowsRuntime::Initialize(std::shared_ptr<ApplicationInitParams> param) {

    WindowsApplication::Initialize(param);
    SceneManager::Instance->LoadScene("Test");
}

void WindowsRuntime::Render() {

    Renderer::Instance->SetViewPort(0, 0, -1, -1);
    SceneManager::Instance->Render(nullptr, nullptr);
    Renderer::Instance->Present();
}

void WindowsRuntime::Tick() {

    WindowsApplication::Tick();
    SceneManager::Instance->Tick();
}

void WindowsRuntime::OnWindowSizeChange(int width, int height) {

    WindowsApplication::OnWindowSizeChange(width, height);
}
