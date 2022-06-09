#include "MaterialD3D11.h"
#include "Functional/RHI/D3D11/RendererD3D11.h"
#include "Functional/RHI/D3D11/RenderContextD3D11.h"
#include "Functional/RHI/D3D11/TextureD3D11.h"

using namespace SingularEngine;

MaterialD3D11::MaterialD3D11(const std::string &path, MaterialType mt) :
    Material(path, mt)
{

}


void MaterialD3D11::Apply() {

    mVS->Bind();
    mPS->Bind();
    mPerMaterial->Bind();
    mDepthStencilState->Bind();
    BindTextures();
}

void MaterialD3D11::BindTextures() {

    ID3D11SamplerState* state = nullptr;

    for(auto& pair : mParamDefines)
    {
        if (pair.second.mMatType == MaterialParameterType::Texture2D)
        {
            auto texture = GetTexture(pair.first);
            if (texture == nullptr)
            {
                continue;
            }
            auto mp = pair.second;
            if (texture->GetTextureType() == TextureType::ImageTexture)
            {
                auto imageTexture = std::dynamic_pointer_cast<TextureD3D11>(texture);
                auto srv = imageTexture->GetSRV();
                BindTexture(mp.mShaderType, mp.mOffset, state, srv);
            }
            else if(texture->GetTextureType() == TextureType::RTTexture)
            {
                auto rt = std::dynamic_pointer_cast<RenderTargetD3D11>(texture);
                auto srv = rt->GetSRV();
                BindTexture(mp.mShaderType, mp.mOffset, state, srv);
            }
            else
            {
                SINGULAR_ASSERT(false);
            }
        }
    }
}

void MaterialD3D11::BindTexture(
    TextureShaderType texShaderType,
    int offset, ID3D11SamplerState *state,
    ID3D11ShaderResourceView *srv) {

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext());

    if (texShaderType == TextureShaderType::VS) {
        context->mDeviceContext->VSSetShaderResources(offset, 1, &srv);
        context->mDeviceContext->VSSetSamplers(offset, 1, &state);
    }
    else if (texShaderType == TextureShaderType::PS) {
        context->mDeviceContext->PSSetShaderResources(offset, 1, &srv);
        context->mDeviceContext->PSSetSamplers(offset, 1, &state);
    }
    else {
        SINGULAR_ASSERT(false);
    }
}
