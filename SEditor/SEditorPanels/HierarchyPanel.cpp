#include <imgui.h>

#include "HierarchyPanel.h"

#include "SEditorWindows/WindowsEditor.h"
#include "Core/Logging/Logger.h"

using namespace SingularEngine;

void HierarchyPanel::Initialize() {

}

void HierarchyPanel::Finalize() {

}

void HierarchyPanel::Render() {

    ImGui::Begin("Hierarchy Window", &mbShowing);
    RenderGameObject(SceneManager::Instance->GetRoot().get());
    ImGui::End();
}

void HierarchyPanel::RenderGameObject(GameObject *obj) {

    ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow;
    if (obj == mSelectedObject) {
        nodeFlags |= ImGuiTreeNodeFlags_Selected;
    }

    if (ImGui::TreeNodeEx(obj->GetName().c_str(), nodeFlags)) {

        if (ImGui::IsItemClicked()) {
            mSelectedObject = obj;
            WindowsEditor::Instance->mInspectorPanel.OnSelectNewGameObject(obj);
        }

        auto children = obj->GetTransform()->GetChildren();
        for (const auto & child : children) {
            RenderGameObject(child->GetOwner());
        }
        ImGui::TreePop();
    }
}
