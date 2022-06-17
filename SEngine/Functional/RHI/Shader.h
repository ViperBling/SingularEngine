#pragma once

namespace SingularEngine
{
    enum class ShaderType
    {
        Unknown = 0,
        VertexShader,
        PixelShader,
    };

    class Shader
    {
    public:
        explicit Shader(ShaderType shaderType) :
            mShaderType(shaderType)
        {}

        virtual ~Shader() = default;

        virtual void Bind() = 0;

    public:
        ShaderType mShaderType;
    };
}