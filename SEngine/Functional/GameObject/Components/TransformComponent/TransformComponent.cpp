#include "TransformComponent.h"

using namespace SingularEngine;


void TransformComponent::Initialize() {

}

void TransformComponent::Finalize() {

}

void TransformComponent::Tick() {

}

void TransformComponent::AddChild(TransformComponent *child) {

    if (std::find(mChildren.begin(), mChildren.end(), child) != mChildren.end()) {
        SINGULAR_ASSERT(false);
        return;
    }
    mChildren.emplace_back(child);
    child->SetParent(this);
}

void TransformComponent::RemoveChild(TransformComponent *child) {

    child->SetParent(nullptr);

    for (auto it = mChildren.begin(); it != mChildren.end(); it++) {
        if (*it == child) {
            mChildren.erase(it);
            return;
        }
    }
}

void TransformComponent::SetPosition(float x, float y, float z) {

    Vector3f v(x, y, z);
    mbRTSMatrixDirty = true;
    mPosition = v;
}

void TransformComponent::SetScale(float x, float y, float z) {

    Vector3f v(x, y, z);
    mbRTSMatrixDirty = true;
    mScale = v;
}

Vector3f TransformComponent::GetEuler() {

    return mRotation.ToEuler();
}

void TransformComponent::SetEuler(float x, float y, float z) {

    auto q = Quaternion::FromRollPitchYawLH(x, y, z);
    mbRTSMatrixDirty = true;
    mRotation = q;
}

Matrix4x4f TransformComponent::GetRTSMatrix() {

    if (mbRTSMatrixDirty)
    {
        CalculateRTSMatrix();
    }
    return mRTSMatrix;
}

Vector3f TransformComponent::GetForward() {

    auto r = BuildMatrixQuaternion(mRotation);
    Vector3f f(0, 0, -1);
    return Normalize(r.TransformVector(f));
}

void TransformComponent::CalculateRTSMatrix() {

    auto r = BuildMatrixQuaternion(mRotation);
    auto s = BuildMatrixScale(mScale.x, mScale.y, mScale.z);
    auto t = BuildMatrixTranslation(mPosition.x, mPosition.y, mPosition.z);
    mRTSMatrix = t * s * r;
    mbRTSMatrixDirty = false;
}
