#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "Core/Math/MathPCH.h"
#include "Functional/RHI/Shader.h"
#include "Functional/RHI/ConstantBuffer.h"
#include "Functional/RHI/DepthStencilState.h"
#include "Functional/RHI/Texture.h"

namespace SingularEngine
{
    class Texture;
    enum class MaterialParameterType
    {
        Unknown,
        Float,
        Vector4,
        Matrix,
        Texture2D,
    };

    enum class TextureShaderType
    {
        VS,
        PS,
    };

    struct MaterialParameter
    {
        MaterialParameterType mMatType;
        int mOffset;
        TextureShaderType mShaderType;
    };

    enum class MaterialType
    {
        MeshRender,
        PostProcess,
        ShadowMapping,
    };

    class Material
    {
    public:
        explicit Material(const std::string& materialName, MaterialType materialType);
        virtual ~Material() = default;
        virtual void Apply() = 0;

        float GetFloat(const std::string& name);
        Vector4f GetVector4(const std::string& name);
        Matrix4x4f GetMatrix(const std::string& name);
        std::shared_ptr<Texture> GetTexture(const std::string& name);
        int GetParamOffset(const std::string& name);
        MaterialParameterType GetParamType(const std::string& name);

        void SetFloat(const std::string& name, float value);
        void SetVector4(const std::string& name, Vector4f value);
        void SetMatrix(const std::string& name, Matrix4x4f value);
        void SetTexture(const std::string& name, const std::shared_ptr<Texture>& value);

        MaterialType GetMaterialType() const { return mMaterialType; }
        const std::string& GetName() const { return mMaterialName; }

        std::shared_ptr<Shader> GetVertexShader() { return mVS; }
        std::shared_ptr<Shader> GetPixelShader() { return mPS; }
        void SetVertexShader(const std::shared_ptr<Shader>& vs) { mVS = vs; }
        void SetPixelShader(const std::shared_ptr<Shader>& ps) { mPS = ps; }

    protected:
        virtual void BindTextures() = 0;

    private:
        bool CheckParamExist(const std::string& name) const;
        void BuildMaterialParamLayout();

    protected:
        MaterialType mMaterialType;
        std::string mMaterialName;
        std::shared_ptr<Shader> mVS;
        std::shared_ptr<Shader> mPS;
        std::shared_ptr<ConstantBuffer> mPerMaterial;
        std::shared_ptr<DepthStencilState> mDepthStencilState;
        std::unordered_map<std::string, float> mFloatParams;
        std::unordered_map<std::string, Vector4f> mVector4Params;
        std::unordered_map<std::string, Matrix4x4f> mMatrixParams;
        std::unordered_map<std::string, std::shared_ptr<Texture>> mTextureParams;

        std::unordered_map<std::string, MaterialParameter> mParamDefines;
    };
}