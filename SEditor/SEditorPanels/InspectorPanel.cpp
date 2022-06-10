#include <imgui.h>

#include "InspectorPanel.h"
#include "Functional/GameObject/GameObject.h"
#include "Core/Logging/Logger.h"

using namespace SingularEngine;

void InspectorPanel::Initialize() {

}

void InspectorPanel::Finalize() {

}

void InspectorPanel::Render() {

    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(100, 250));
    ImGui::Begin("Inspector Window", &mbShowing);

    if (mInspectingGameObject != nullptr) {

        ImGui::Text("%s", mInspectingGameObject->GetName().c_str());
        TransformComponentEditor::Render(mTransformComponent);
        CameraComponentEditor::Render(mCameraComponent);
        MeshRenderComponentEditor::Render(mMeshRenderComponent);
        LightComponentEditor::Render(mLightRenderComponent);
    }

    ImGui::End();
    ImGui::PopStyleVar();
}

void InspectorPanel::OnSelectNewGameObject(GameObject *target) {

    mInspectingGameObject = target;
    mTransformComponent = mInspectingGameObject->GetTransform();
    mCameraComponent = mInspectingGameObject->GetComponent<CameraComponent>();
    mMeshRenderComponent = mInspectingGameObject->GetComponent<MeshRenderComponent>();
    mLightRenderComponent = mInspectingGameObject->GetComponent<LightComponent>();
}
