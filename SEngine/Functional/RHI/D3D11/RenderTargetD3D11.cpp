#include "RenderTargetD3D11.h"
#include "Functional/RHI/D3D11/RenderContextD3D11.h"
#include "Functional/RHI/D3D11/RendererD3D11.h"

#include "Platform/Assert.h"

using namespace SingularEngine;


RenderTargetD3D11::RenderTargetD3D11(RenderTargetDesc rtDesc, ID3D11Device *device) :
    RenderTarget(rtDesc)
{

    CreateRenderTarget(rtDesc, device);
    CreateDepthStencilResource(rtDesc, device);
}

RenderTargetD3D11::RenderTargetD3D11(RenderTargetDesc rtDesc, ID3D11Device *device, IDXGISwapChain *swapChain) :
    RenderTarget(rtDesc)
{

    CreateRenderTargetFromSwapChain(rtDesc, device, swapChain);
    CreateDepthStencilResource(rtDesc, device);
}

RenderTargetD3D11::~RenderTargetD3D11() {

    ClearRenderTarget();
    ClearDepthStencilResource();
}

void RenderTargetD3D11::Resize(int width, int height) {

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext());

    if (mDesc.rtUsage == RenderTargetUsage::Default) {

        RenderTarget::Resize(width, height);
        if (mRenderTargetTexture == nullptr) {

            ClearRenderTarget();
            ClearDepthStencilResource();
            auto hr = context->mSwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
            SINGULAR_ASSERT(SUCCEEDED(hr));
            ID3D11Texture2D* pBuffer;
            hr = context->mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
            SINGULAR_ASSERT(SUCCEEDED(hr));
            hr = context->mDevice->CreateRenderTargetView(pBuffer, nullptr, &mRenderTargetView);
            SINGULAR_ASSERT(SUCCEEDED(hr));
            pBuffer->Release();
            mDesc.width = width;
            mDesc.height = height;
            CreateDepthStencilResource(mDesc, context->mDevice);
        }
        else {

            ClearRenderTarget();
            ClearDepthStencilResource();
            mDesc.width = width;
            mDesc.height = height;
            CreateRenderTarget(mDesc, context->mDevice);
            CreateDepthStencilResource(mDesc, context->mDevice);
        }
    }
    else if (mDesc.rtUsage == RenderTargetUsage::ShadowMap) {
        SINGULAR_ASSERT(false);
    }
}

void RenderTargetD3D11::Bind() {

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext());

    ID3D11SamplerState* state = nullptr;
    if (mDesc.rtUsage == RenderTargetUsage::ShadowMap) {
        // shadow map bind slot 1 in our engine
        context->mDeviceContext->PSSetShaderResources(1, 1, &mDepthStencilSRV);
        context->mDeviceContext->PSSetSamplers(1, 1, &state);
    }
    else {
        SINGULAR_ASSERT(false);
    }
}

void RenderTargetD3D11::ClearRenderTarget() {

    if (mRenderTargetView != nullptr) {
        mRenderTargetView->Release();
        mRenderTargetView = nullptr;
    }

    if (mRenderTargetTexture != nullptr) {
        mRenderTargetTexture->Release();
        mRenderTargetTexture = nullptr;
    }

    if (mShaderResourceView != nullptr) {
        mShaderResourceView->Release();
        mShaderResourceView = nullptr;
    }
}

void RenderTargetD3D11::ClearDepthStencilResource() {

    if (mDepthStencilView != nullptr) {
        mDepthStencilView->Release();
        mDepthStencilView = nullptr;
    }

    if (mDepthStencilTexture != nullptr) {
        mDepthStencilTexture->Release();
        mDepthStencilTexture = nullptr;
    }
}

void RenderTargetD3D11::CreateRenderTarget(RenderTargetDesc rtDesc, ID3D11Device *device) {

    if (rtDesc.rtUsage == RenderTargetUsage::Default)
    {
        D3D11_TEXTURE2D_DESC textureDesc;
        D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
        D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
        // render texture
        ZeroMemory(&textureDesc, sizeof(textureDesc));
        textureDesc.Width = rtDesc.width;
        textureDesc.Height = rtDesc.height;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;
        auto result = device->CreateTexture2D(&textureDesc, nullptr, &mRenderTargetTexture);
        SINGULAR_ASSERT(SUCCEEDED(result));
        // render target view
        renderTargetViewDesc.Format = textureDesc.Format;
        renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        renderTargetViewDesc.Texture2D.MipSlice = 0;
        result = device->CreateRenderTargetView(mRenderTargetTexture, &renderTargetViewDesc, &mRenderTargetView);
        SINGULAR_ASSERT(SUCCEEDED(result));
        // shader resource view
        shaderResourceViewDesc.Format = textureDesc.Format;
        shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
        shaderResourceViewDesc.Texture2D.MipLevels = 1;
        result = device->CreateShaderResourceView(mRenderTargetTexture, &shaderResourceViewDesc, &mShaderResourceView);
    }
    else if (rtDesc.rtUsage == RenderTargetUsage::ShadowMap)
    {
        mRenderTargetTexture = nullptr;
        mRenderTargetView = nullptr;
        mShaderResourceView = nullptr;
    }
    else
    {
        SINGULAR_ASSERT(false);
    }
}

void RenderTargetD3D11::CreateRenderTargetFromSwapChain(
    RenderTargetDesc rtDesc, ID3D11Device *device, IDXGISwapChain *swapChain)
{
    if (rtDesc.rtUsage == RenderTargetUsage::Default)
    {
        // Get the pointer to the back buffer.
        ID3D11Texture2D* backBufferPtr;
        auto hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
        SINGULAR_ASSERT(hr >= 0);
        // Create the render target view with the back buffer pointer.
        hr = device->CreateRenderTargetView(backBufferPtr, nullptr, &mRenderTargetView);
        SINGULAR_ASSERT(hr >= 0);
        // Release pointer to the back buffer as we no longer need it.
        backBufferPtr->Release();
        backBufferPtr = nullptr;
        mRenderTargetTexture = nullptr;
        mShaderResourceView = nullptr;
    }
    else
    {
        SINGULAR_ASSERT(false);
    }
}

void RenderTargetD3D11::CreateDepthStencilResource(RenderTargetDesc rtDesc, ID3D11Device *device) {

    if (rtDesc.rtUsage == RenderTargetUsage::Default)
    {
        // depth stencil buffer
        D3D11_TEXTURE2D_DESC descDepth{};
        descDepth.Width = rtDesc.width;
        descDepth.Height = rtDesc.height;
        descDepth.MipLevels = 1;
        descDepth.ArraySize = 1;
        // Most video cards come with a 32 bit depth buffer, it is then up to you how you want to use those 32 bits.
        // set the depth buffer format to DXGI_FORMAT_D24_UNORM_S8_UINT.
        // What this means is that we use the depth buffer as both a depth buffer and a stencil buffer,
        // and the format of the buffer is set to 24 bits for the depth channel and 8 bits for the stencil channel.
        // http://www.rastertek.com/dx11tut35.html
        descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        descDepth.SampleDesc.Count = 1;
        descDepth.SampleDesc.Quality = 0;
        descDepth.Usage = D3D11_USAGE_DEFAULT;
        descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        descDepth.CPUAccessFlags = 0;
        descDepth.MiscFlags = 0;
        auto hr = device->CreateTexture2D( &descDepth, nullptr, &mDepthStencilTexture);
        SINGULAR_ASSERT(SUCCEEDED(hr));

        //  depth stencil view
        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV{};
        descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        descDSV.Texture2D.MipSlice = 0;
        hr = device->CreateDepthStencilView(mDepthStencilTexture, &descDSV, &mDepthStencilView);
        SINGULAR_ASSERT(SUCCEEDED(hr));
    }
    else if (rtDesc.rtUsage == RenderTargetUsage::ShadowMap)
    {
        // depth stencil buffer
        D3D11_TEXTURE2D_DESC descDepth{};
        descDepth.Width = rtDesc.width;
        descDepth.Height = rtDesc.height;
        descDepth.MipLevels = 1;
        descDepth.ArraySize = 1;
        //https://docs.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-depth-stencil#reading-the-depth-stencil-buffer-as-a-texture
        descDepth.Format = DXGI_FORMAT_R32_TYPELESS;
        descDepth.SampleDesc.Count = 1;
        descDepth.SampleDesc.Quality = 0;
        descDepth.Usage = D3D11_USAGE_DEFAULT;
        //https://docs.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-depth-stencil#reading-the-depth-stencil-buffer-as-a-texture
        descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL | D3D10_BIND_SHADER_RESOURCE;
        descDepth.CPUAccessFlags = 0;
        descDepth.MiscFlags = 0;
        auto hr = device->CreateTexture2D( &descDepth, nullptr, &mDepthStencilTexture);
        SINGULAR_ASSERT(SUCCEEDED(hr));
        //  depth stencil view
        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV{};
        descDSV.Format = DXGI_FORMAT_D32_FLOAT;
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        descDSV.Texture2D.MipSlice = 0;
        hr = device->CreateDepthStencilView(mDepthStencilTexture, &descDSV, &mDepthStencilView);
        SINGULAR_ASSERT(SUCCEEDED(hr));
        // shader resource view
        D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc{};
        // https://takinginitiative.wordpress.com/2011/05/15/directx10-tutorial-10-shadow-mapping/
        shaderResourceViewDesc.Format = DXGI_FORMAT_R32_FLOAT;
        shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
        shaderResourceViewDesc.Texture2D.MipLevels = 1;
        hr = device->CreateShaderResourceView(mDepthStencilTexture, &shaderResourceViewDesc, &mDepthStencilSRV);
        SINGULAR_ASSERT(SUCCEEDED(hr));
    }
    else
    {
        SINGULAR_ASSERT(false);
    }
}

std::shared_ptr<RenderTargetD3D11> RenderTargetD3D11::CreateFromSwapChain(
    RenderTargetDesc rtDesc,
    ID3D11Device *device,
    IDXGISwapChain *swapChain)
{
    return std::make_shared<RenderTargetD3D11>(rtDesc, device, swapChain);
}

std::shared_ptr<RenderTargetD3D11> RenderTargetD3D11::Create(RenderTargetDesc rtDesc, ID3D11Device *device) {

    return std::make_shared<RenderTargetD3D11>(rtDesc, device);
}
