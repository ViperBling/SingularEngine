#pragma once

#include <vector>

#include "Functional/GameObject/Components/Component.h"
#include "Core/Math/MathPCH.h"

namespace SingularEngine
{
    class TransformComponent : public Component
    {
    public:
        TransformComponent(GameObject* owner) :
            Component(owner),
            mPosition(0, 0, 0),
            mScale(1, 1, 1),
            mRotation(0, 0, 0, 1)
        {}

        void Initialize() override;
        void Finalize() override;
        void Tick() override;

        TransformComponent* GetParent() { return mParent; }
        const std::vector<TransformComponent*>& GetChildren() { return mChildren; }
        Vector3f GetPosition() {return mPosition; }
        Vector3f GetScale() {return mScale;}

        void SetParent(TransformComponent* parent ) { mParent = parent; }

        void AddChild(TransformComponent* child);
        void RemoveChild(TransformComponent* child);

        void SetPosition(float x, float y, float z);
        void SetScale(float x, float y, float z);
        Vector3f GetEuler();
        void SetEuler(float x, float y, float z);
        Matrix4x4f GetRTSMatrix();
        Vector3f GetForward();

    private:
        void CalculateRTSMatrix();

    private:
        Vector3f mPosition;
        Vector3f mScale;
        Quaternion mRotation;
        TransformComponent* mParent;
        std::vector<TransformComponent*> mChildren;
        Matrix4x4f mRTSMatrix;
        bool mbRTSMatrixDirty = true;

    };
}