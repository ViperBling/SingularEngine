#pragma once

#include <d3d11.h>

#include "Functional/RHI/Material.h"

namespace SingularEngine
{
    class MaterialD3D11 : public Material
    {
    public:
        explicit MaterialD3D11(const std::string& path, MaterialType mt);
        ~MaterialD3D11() override = default;

        void Apply() override;

    protected:
        void BindTextures() override;
        void BindTexture(TextureShaderType texShaderType, int offset, ID3D11SamplerState* state, ID3D11ShaderResourceView* srv);
    };
}