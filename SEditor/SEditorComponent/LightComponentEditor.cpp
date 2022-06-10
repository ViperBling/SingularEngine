#include <imgui.h>

#include "LightComponentEditor.h"
#include "Functional/GameObject/GameObject.h"

using namespace SingularEngine;

const char* LightTypeName[] = {"Directional", "Spot", "Point"};

void LightComponentEditor::Render(const std::shared_ptr<LightComponent> &light) {

    if (light == nullptr) return;

    ImGui::Separator();
    ImGui::Text("LightComponent");

    int lightType = (int)light->GetLightType();
    ImGui::Combo("Projection", &lightType, LightTypeName, IM_ARRAYSIZE(LightTypeName), IM_ARRAYSIZE(LightTypeName));

    if ((LightType)lightType == LightType::Directional) {

        auto direction = light->GetOwner()->GetTransform()->GetForward();
        ImGui::Text("Direction: %f, %f, %f", direction.x, direction.y, direction.z);
    }

    Color& color = light->GetColor();
    ImGui::DragFloat3("Color", reinterpret_cast<float *>(&color), 0.01f, 0.0f, 1.0f);
    float& intensity = light->GetIntensity();

    ImGui::DragFloat("Intensity", reinterpret_cast<float *>(&intensity), 0.01, 0.0f, 10.0f);
    light->SetLightType((LightType)lightType);
}
