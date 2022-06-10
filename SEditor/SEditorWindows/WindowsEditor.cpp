#include <imgui.h>

#include "WindowsEditor.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/GUI/GUIManager.h"
#include "Functional/Scene/SceneManager.h"

using namespace SingularEngine;

WindowsEditor* WindowsEditor::Instance = nullptr;

static void ShowDockingDisableMessage() {

    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
    ImGui::Text("Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code, or ");
    ImGui::SameLine(0.0f, 0.0f);
    if (ImGui::SmallButton("click here"))
    {
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    }
}

WindowsEditor::WindowsEditor() {

    SINGULAR_ASSERT(Instance == nullptr);
    Instance = this;
}

void WindowsEditor::Initialize(std::shared_ptr<ApplicationInitParams> param) {

    WindowsApplication::Initialize(param);
    mHierarchyPanel.Initialize();
    mLogPanel.Initialize();
    mGamePanel.Initialize();
    SceneManager::Instance->LoadScene("Test");
    Logger::Info("Editor Init Ok!");
}

void WindowsEditor::Tick() {

    WindowsApplication::Tick();
    SceneManager::Instance->Tick();
}

void WindowsEditor::Render() {

    GUIManager::Begin();

    RenderEditorBegin();
    mHierarchyPanel.Render();
    mLogPanel.Render();
    mGamePanel.Render();
    mInspectorPanel.Render();
    RenderEditorEnd();
    GUIManager::End();

    Renderer::Instance->Present();
}

void WindowsEditor::Finalize() {

    mHierarchyPanel.Finalize();
    mLogPanel.Finalize();
    mGamePanel.Finalize();
    mInspectorPanel.Finalize();
    WindowsApplication::Finalize();
}

void WindowsEditor::OnWindowSizeChange(int width, int height) {

    WindowsApplication::OnWindowSizeChange(width, height);
}

void WindowsEditor::RenderEditorBegin() {

    static bool open = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
    {
        window_flags |= ImGuiWindowFlags_NoBackground;
    }

    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
    {
        window_flags |= ImGuiWindowFlags_NoBackground;
    }
    if (!opt_padding)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    }

    ImGui::Begin("DockSpace Demo", &open, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    else
    {
        ShowDockingDisableMessage();
    }
}

void WindowsEditor::RenderEditorEnd() {

    ImGui::End();
}
