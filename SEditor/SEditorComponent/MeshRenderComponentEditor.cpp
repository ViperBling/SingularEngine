#include <imgui.h>

#include "MeshRenderComponentEditor.h"

using namespace SingularEngine;

void MeshRenderComponentEditor::Render(const std::shared_ptr<MeshRenderComponent> &meshRender) {

    if (meshRender == nullptr) return;

    ImGui::Separator();
    ImGui::Text("MeshRenderComponent");
    ImGui::Text("Materials");

    for (int i = 0; i < meshRender->GetMaterialCount(); i++) {

        auto material = meshRender->GetMaterial(i);
        auto& name = material->GetName();

        ImGui::Text("%d : %s", i, name.c_str());
    }

    bool& castShadow = meshRender->GetCastShadowFlag();
    ImGui::Checkbox("cast shadow", &castShadow);
}
