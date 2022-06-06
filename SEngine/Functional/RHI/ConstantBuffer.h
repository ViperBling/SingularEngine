#pragma once

#include "Core/Math/MathPCH.h"

namespace SingularEngine
{
    enum class ConstantBufferDataType
    {
        PerMaterial,
        PerObject,
        PerFrame,
    };

    struct ConstantBufferDataDirectionalLight
    {
        Vector4f mDirection;
        Vector4f mColor;
        Vector4f mIntensity;
    };

    struct ConstantBufferDataSpotLight
    {
        Vector4f mDirection;
        Vector4f mPosition;
        Vector4f mColor;
        Vector4f mIntensity;
    };

    struct ConstantBufferDataPointLight
    {
        Vector4f mPosition;
        Vector4f mColor;
        Vector4f mIntensity;
    };

    struct ConstantBufferDataPerFrame
    {
        Matrix4x4f mViewMatrix;
        Matrix4x4f mProjectionMatrix;
        Matrix4x4f mVP;
        ConstantBufferDataDirectionalLight mDirectionLight;
        ConstantBufferDataSpotLight mSpotLight[4];
        ConstantBufferDataPointLight mPointLight[4];
        Matrix4x4f mLightViewProj;
    };

    struct ConstantBufferDataPerObject
    {
        Matrix4x4f mWorldMatrix;
    };

    class ConstantBuffer
    {
    public:
        explicit ConstantBuffer(ConstantBufferDataType cbDataType, int size);
        virtual ~ConstantBuffer();

        void* GetData() { return mData; }
        ConstantBufferDataType GetDataType() const { return mDataType; }

        virtual void Bind() = 0;

    protected:
        ConstantBufferDataType mDataType;
        int mSize;
        void* mData = nullptr;
    };
}