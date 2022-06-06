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
    };
}