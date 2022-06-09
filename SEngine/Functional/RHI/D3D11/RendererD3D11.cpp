#include <d3dcompiler.h>
#include <iostream>

#include "RendererD3D11.h"
#include "Platform/Assert.h"
#include "Resource/AssetManager/AssetLoader.h"

#include "Functional/RHI/D3D11/DepthStencilStateD3D11.h"
#include "Functional/RHI/D3D11/MaterialD3D11.h"
#include "Functional/RHI/D3D11/MeshD3D11.h"
#include "Functional/RHI/D3D11/RasterizationStateD3D11.h"
#include "Functional/RHI/D3D11/RendererD3D11.h"
#include "Functional/RHI/D3D11/RenderContextD3D11.h"
#include "Functional/RHI/D3D11/RenderItemD3D11.h"
#include "Functional/RHI/D3D11/ShaderD3D11.h"
#include "Functional/RHI/D3D11/TextureD3D11.h"
#include "Functional/RHI/D3D11/VertexBufferD3D11.h"




using namespace SingularEngine;

void RendererD3D11::CreateDeviceContext() {

    HRESULT hr;
    IDXGIFactory* factory;
    IDXGIAdapter* adapter;
    IDXGIOutput* adapterOut;
    unsigned int numModes;
    size_t strLen;
    DXGI_MODE_DESC* displayModeList;

    int error;
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    D3D_FEATURE_LEVEL featureLevel;

    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;
    IDXGISwapChain* swapChain;

    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
    SINGULAR_ASSERT(hr >= 0);
    hr = factory->EnumAdapters(0, &adapter);
    SINGULAR_ASSERT(hr >= 0);
    hr = adapter->EnumOutputs(0, &adapterOut);
    SINGULAR_ASSERT(hr >= 0);
    hr = adapterOut->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
    SINGULAR_ASSERT(hr >= 0);
    displayModeList = new DXGI_MODE_DESC[numModes];
    SINGULAR_ASSERT(displayModeList);
    hr = adapterOut->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
    SINGULAR_ASSERT(hr >= 0);

    {
        DXGI_ADAPTER_DESC adapterDesc;
        hr = adapter->GetDesc(&adapterDesc);
        SINGULAR_ASSERT(hr >= 0);
        auto videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
        char videoCardDescription[128];
        error = wcstombs_s(&strLen, videoCardDescription, 128, adapterDesc.Description, 128);
        SINGULAR_ASSERT(error == 0);
    }

    delete [] displayModeList;
    displayModeList = nullptr;

    adapterOut->Release();
    adapterOut = nullptr;

    adapter->Release();
    adapter = nullptr;

    factory->Release();
    factory = nullptr;

    // Initialize the swap chain description.
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    // Set to a single back buffer.
    swapChainDesc.BufferCount = 1;
    // Set the width and height of the back buffer.
    swapChainDesc.BufferDesc.Width = mResolutionWidth;
    swapChainDesc.BufferDesc.Height = mResolutionHeight;
    // Set regular 32-bit surface for the back buffer.
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // Set the refresh rate of the back buffer.
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    // Set the usage of the back buffer.
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    // Set the handle for the window to render to.
    swapChainDesc.OutputWindow = mHWND;
    // Turn multi sampling off.
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    // Set to full screen or windowed mode.
    swapChainDesc.Windowed = true;
    // Set the scan line ordering and scaling to unspecified.
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    // Discard the back buffer contents after presenting.
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    // Don't set the advanced flags.
    swapChainDesc.Flags = 0;
    // Set the feature level to DirectX 11.
    featureLevel = D3D_FEATURE_LEVEL_11_1;

    UINT creationFlags = 0;
#ifdef SINGULAR_BUILD_DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        &featureLevel,
        1,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );
    SINGULAR_ASSERT(hr >= 0);

    RenderTargetDesc desc{};
    desc.rtUsage = RenderTargetUsage::Default;
    desc.width = mResolutionWidth;
    desc.height = mResolutionHeight;
    auto renderTarget = RenderTargetD3D11::CreateFromSwapChain(desc, device, swapChain);
    mContext = std::make_shared<RenderContextD3D11>(device, deviceContext, swapChain, renderTarget);
}

void RendererD3D11::ReleaseDeviceContext() {

    if (mContext != nullptr) {
        mContext.reset();
        mContext = nullptr;
    }
}

void RendererD3D11::Initialize(CreateRendererContextParam param) {

    mAPIType = RenderAPI::D3D11;
    mResolutionWidth = param.mResolutionWidth;
    mResolutionHeight = param.mResolutionHeight;
    mHWND = param.mHWND;
    CreateDeviceContext();
    CreateDefaultRasterizationState();
}

void RendererD3D11::Finalize() {

    ReleaseDeviceContext();
}

void RendererD3D11::ResizeResolution(int width, int height) {

    mResolutionWidth = width;
    mResolutionHeight = height;

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(mContext);
    auto mainRT = context->mMainRT;

    SetRenderTarget(nullptr);
    ClearRenderTarget(nullptr, 0.1f, 0.1f, 0.1f, 1.0f);

    if (mainRT != nullptr) {
        mainRT->Resize(width, height);
    }
}

void RendererD3D11::SetViewPort(int x, int y, int w, int h) {

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(mContext);
    D3D11_VIEWPORT viewport;

    viewport.Width = w == -1 ? (float)mResolutionWidth : (float)w;
    viewport.Height = h == -1 ? (float)mResolutionHeight : (float)h;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = (float)x;
    viewport.TopLeftY = (float)y;

    context->mDeviceContext->RSSetViewports(1, &viewport);
}

void RendererD3D11::Present() {

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(mContext);
    context->mSwapChain->Present(1, 0);
}

void RendererD3D11::ClearRenderTarget(std::shared_ptr<RenderTarget> rt, float r, float g, float b, float a) {

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(mContext);
    float color[4] = {r, g, b, a};

    if (rt == nullptr) {
        auto rtv = context->mMainRT->GetRenderTargetView();
        auto dsv = context->mMainRT->GetDepthStencilView();

        if (rtv != nullptr) {
            context->mDeviceContext->ClearRenderTargetView(rtv, color);
        }
        if (dsv != nullptr) {
            context->mDeviceContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0, 0);
        }
    }
    else {
        auto d3d11rt = std::dynamic_pointer_cast<RenderTargetD3D11>(rt);
        auto rtv = d3d11rt->GetRenderTargetView();
        auto dsv = d3d11rt->GetDepthStencilView();

        if (rtv != nullptr) {
            context->mDeviceContext->ClearRenderTargetView(rtv, color);
        }
        if (dsv != nullptr) {
            context->mDeviceContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0, 0);
        }
    }
}

void RendererD3D11::SetRenderTarget(const std::shared_ptr<RenderTarget> &rt) {

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(mContext);

    if (rt == nullptr) {
        auto mainRT = context->mMainRT;
        auto rtv = mainRT->GetRenderTargetView();
        auto dsv = mainRT->GetDepthStencilView();
        context->mDeviceContext->OMSetRenderTargets(1, &rtv, dsv);
    }
    else {
        auto d3d11rt = std::dynamic_pointer_cast<RenderTargetD3D11>(rt);
        auto rtv = d3d11rt->GetRenderTargetView();
        auto dsv = d3d11rt->GetDepthStencilView();
        context->mDeviceContext->OMSetRenderTargets(1, &rtv, dsv);
    }
}

void RendererD3D11::SetRasterizationState(const std::shared_ptr<RasterizationState> &rs) {

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(mContext);

    if (rs == nullptr) {
        auto state = std::dynamic_pointer_cast<RasterizationStateD3D11>(mDefaultRasterizationState)->GetInternalState();
        context->mDeviceContext->RSSetState(state);
    }
    else {
        auto state = std::dynamic_pointer_cast<RasterizationStateD3D11>(rs)->GetInternalState();
        context->mDeviceContext->RSSetState(state);
    }
}

std::shared_ptr<Mesh> RendererD3D11::CreateMesh(const std::string &path) {

    auto param = AssetLoader::LoadMesh(path);
    auto mesh = MeshD3D11::Create(param);

    return mesh;
}

std::shared_ptr<Mesh> RendererD3D11::CreateMesh(const std::shared_ptr<MeshCreateParam> &param) {

    return MeshD3D11::Create(param);
}

std::shared_ptr<RenderTarget> RendererD3D11::CreateRenderTarget(RenderTargetDesc desc) {

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(mContext);
    return RenderTargetD3D11::Create(desc, context->mDevice);
}

std::shared_ptr<Shader> RendererD3D11::CreateShader(const std::string &path, ShaderType shaderType) {

    if (shaderType == ShaderType::VertexShader) {
        return VertexShaderD3D11::Create(path);
    }
    else if (shaderType == ShaderType::PixelShader) {
        return PixelShaderD3D11::Create(path);
    }
    else {
        SINGULAR_ASSERT(false);
        return nullptr;
    }
}

std::shared_ptr<Material> RendererD3D11::CreateMaterial(const std::string &materialPath, MaterialType mt) {

    return std::make_shared<MaterialD3D11>(materialPath, mt);
}

std::shared_ptr<DepthStencilState> RendererD3D11::CreateDepthStencilState() {

    return std::make_shared<DepthStencilStateD3D11>();
}

std::shared_ptr<RenderItem> RendererD3D11::CreateRenderItem(
    const std::shared_ptr<Mesh> &mesh,
    const std::vector<std::shared_ptr<Material>> &materials,
    const std::shared_ptr<ConstantBuffer> &perObject)
{

    return RenderItemD3D11::Create(mesh, materials, perObject);
}

std::shared_ptr<RenderItem> RendererD3D11::CreateRenderItem(
    const std::shared_ptr<Mesh> &mesh,
    const std::shared_ptr<ConstantBuffer> &perObject)
{
    return RenderItemD3D11::Create(mesh, perObject);
}

std::shared_ptr<ConstantBuffer> RendererD3D11::CreateConstantBuffer(ConstantBufferDataType dt, int size) {

    auto cb = ConstantBufferD3D11::Create(dt, size);
    return cb;
}

std::shared_ptr<Texture> RendererD3D11::CreateTexture(const std::string &path) {

    auto raw = AssetLoader::LoadRawTexture(path);
    return TextureD3D11::Create(raw);
}

std::shared_ptr<RasterizationState> RendererD3D11::CreateRasterizationState(const RasterizationStateDesc &desc) {

    return std::make_shared<RasterizationStateD3D11>(desc);
}
