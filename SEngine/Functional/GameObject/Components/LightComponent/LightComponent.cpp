#include "LightComponent.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/Scene/SceneManager.h"

using namespace SingularEngine;


void LightComponent::Initialize() {

    SceneManager::Instance->RegisterLight(this);
}

void LightComponent::Finalize() {

    SceneManager::Instance->UnregisterLight(this);
}

void LightComponent::Tick() {

}

void LightComponent::SetLightType(LightType lt) {

    if (lt == LightType::Spot || lt == LightType::Point) {
        Logger::Error("Unsupported Light Type!");
        return;
    }
    mLightType = lt;
}

Matrix4x4f LightComponent::GetLightViewProjMatrix() {

    Vector3f eye = GetOwner()->GetTransform()->GetPosition();
    Vector3f up(0, 1, 0);
    Vector3f direction = GetOwner()->GetTransform()->GetForward();
    Vector3f focus = eye + direction;

    Matrix4x4f ret;
    if (mLightType == LightType::Directional)
    {
        // todo: how to correctly set these parameters?
        auto view = BuildMatrixViewLookatLH(eye, focus, up);
        auto proj = BuildMatrixOrthographicDX(64, 64, 10, 50);
        ret = proj * view;
    }
    else
    {
        SINGULAR_ASSERT(false);
    }
    return ret;
}
