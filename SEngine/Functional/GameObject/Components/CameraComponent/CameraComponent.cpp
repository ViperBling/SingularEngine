#include "CameraComponent.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/Scene/SceneManager.h"

using namespace SingularEngine;

void CameraComponent::Initialize() {

    SceneManager::Instance->RegisterCamera(this);
}

void CameraComponent::Finalize() {

    SceneManager::Instance->UnregisterCamera(this);
}

void CameraComponent::Tick() {

}

const Matrix4x4f &CameraComponent::GetProjectionMatrix() {

    if (mProjectionMatrixDirty) {
        CalculateProjectionMatrix();
    }
    return mProjectionMatrix;
}

void CameraComponent::CalculateProjectionMatrix() {

    if (mProjectionType == CameraProjectionType::Perspective)
    {
        mProjectionMatrix = BuildMatrixPerspectiveFovDX(mFov, mAspectRatio, mNear, mFar);
    }
    else
    {
        mProjectionMatrix = BuildMatrixOrthographicDX(mViewWidth, mViewHeight, mNear, mFar);
    }
    mProjectionMatrixDirty = false;
}

const Matrix4x4f &CameraComponent::GetViewMatrix() {

    auto transform = GetOwner()->GetTransform();
    auto eye = transform->GetPosition();

    Vector3f up(0, 1, 0);
    Vector3f look(0, 0, 0);
    mViewMatrix = BuildMatrixViewLookatLH(eye, look, up);

    return mViewMatrix;
}
