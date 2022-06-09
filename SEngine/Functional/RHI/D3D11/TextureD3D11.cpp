#include "TextureD3D11.h"
#include "Functional/RHI/D3D11/RenderContextD3D11.h"
#include "Functional/RHI/Renderer.h"
#include "Platform/Assert.h"

using namespace SingularEngine;


TextureD3D11::~TextureD3D11() {

    if (mTexture != nullptr) {
        mTexture->Release();
        mTexture = nullptr;
    }
    if (mSRV != nullptr) {
        mSRV->Release();
        mSRV = nullptr;
    }
}

std::shared_ptr<TextureD3D11> TextureD3D11::Create(const std::shared_ptr<RawTexture> &rawTexture) {

    ID3D11Texture2D* texture;
    ID3D11ShaderResourceView* srv;

    D3D11_SUBRESOURCE_DATA initData;
    initData.pSysMem = rawTexture->GetData();
    initData.SysMemPitch = rawTexture->GetWidth() * rawTexture->GetPixelBytes();
    initData.SysMemSlicePitch = 0;

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = rawTexture->GetWidth();
    desc.Height = rawTexture->GetHeight();
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_IMMUTABLE;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext());
    auto hr = context->mDevice->CreateTexture2D( &desc, &initData, &texture);
    SINGULAR_ASSERT(SUCCEEDED(hr));

    D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
    SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    SRVDesc.Texture2D.MipLevels = 1;

    hr = context->mDevice->CreateShaderResourceView(texture, &SRVDesc, &srv);
    SINGULAR_ASSERT(SUCCEEDED(hr));

    return std::make_shared<TextureD3D11>(rawTexture, texture, srv);
}