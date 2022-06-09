#pragma once

#include "Functional/GameObject/Components/Component.h"
#include "Core/Math/MathPCH.h"

namespace SingularEngine
{
    enum class CameraProjectionType
    {
        Perspective = 0,
        Orthographic
    };

    class CameraComponent : public Component
    {
    public:
        CameraComponent() = delete;
        CameraComponent(GameObject* owner) :
            Component(owner),
            mProjectionType(CameraProjectionType::Perspective),
            mNear(0.1f),
            mFar(2000.0f),
            mFov(PI / 3.0f),
            mAspectRatio(16 / 9.),
            mViewWidth(160),
            mViewHeight(90)
        {}

        void Initialize() override;
        void Finalize() override;
        void Tick() override;

        CameraProjectionType GetProjectionType() { return mProjectionType; }
        float GetNear() const { return mNear; }
        float GetFar() const { return mFar; }
        float GetFov() const { return mFov; }
        float GetAspectRatio() const { return mAspectRatio; };
        float GetViewWidth() const { return mViewWidth; }
        float GetViewHeight() const { return mViewHeight; }

        void SetProjectionType(CameraProjectionType pt) {
            mProjectionMatrixDirty = pt != mProjectionType;
            mProjectionType = pt;
        }
        void SetNear(float nearPlane) { mProjectionMatrixDirty = true; mNear = nearPlane; }
        void SetFar(float farPlane) { mProjectionMatrixDirty = true; mFar = farPlane; }
        void SetAspectRatio(float ar) { mProjectionMatrixDirty = true; mAspectRatio = ar; }
        void SetViewWidth(float vw) { mProjectionMatrixDirty = true; mViewWidth = vw; }
        void SetViewHeight(float vh) { mProjectionMatrixDirty = true; mViewHeight = vh; }


        const Matrix4x4f& GetProjectionMatrix();
        void CalculateProjectionMatrix();
        const Matrix4x4f& GetViewMatrix();

    private:
        CameraProjectionType mProjectionType;
        float mNear;
        float mFar;
        float mFov;
        float mAspectRatio;
        float mViewWidth;
        float mViewHeight;
        Matrix4x4f mProjectionMatrix;
        Matrix4x4f mViewMatrix;
        bool mProjectionMatrixDirty = true;
    };
}