#include <imgui.h>
#include "CameraComponentEditor.h"

using namespace SingularEngine;

void CameraComponentEditor::Render(const std::shared_ptr<CameraComponent> &camera) {

    if (camera == nullptr) return;

    int selectedType = (int)camera->GetProjectionType();
    float cfar = camera->GetFar();
    float cnear = camera->GetNear();

    const char* CameraProjectionType[] = {"perspective", "orthographic"};

    ImGui::Separator();
    ImGui::Text("camera");
    ImGui::Combo("projection", &selectedType, CameraProjectionType, IM_ARRAYSIZE(CameraProjectionType), IM_ARRAYSIZE(CameraProjectionType));

    if (selectedType == 0) {

        float fov = camera->GetFov();
        float aspectRatio = camera->GetAspectRatio();

        ImGui::DragFloat("Fov", &fov, 0.001, 0.001, PI/2);
        ImGui::DragFloat("Aspect Ratio", &aspectRatio, 0.001, 0.001, 10);
        camera->SetFov(fov);
        camera->SetAspectRatio(aspectRatio);
        camera->SetProjectionType(CameraProjectionType::Perspective);
    }
    else if (selectedType == 1) {

        float viewWidth = camera->GetViewWidth();
        float viewHeight = camera->GetViewHeight();

        ImGui::DragFloat("Width", &viewWidth, 1, 1, 100000);
        ImGui::DragFloat("Height", &viewHeight, 1, 1, 100000);
        camera->SetViewWidth(viewWidth);
        camera->SetViewHeight(viewHeight);
        camera->SetProjectionType(CameraProjectionType::Orthographic);
    }
    else {}

    ImGui::DragFloat("Far", &cfar, 1, 1, 100000);
    ImGui::DragFloat("Near", &cnear, 0.01, 0.01, 100000);

    camera->SetFar(cfar);
    camera->SetNear(cnear);
    if (cfar <= cnear)
    {
        ImGui::Text("Far mush larger then Near!");
    }
}
