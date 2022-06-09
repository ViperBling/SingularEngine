#include "RasterizationStateD3D11.h"
#include "Functional/RHI/D3D11/RenderContextD3D11.h"
#include "Functional/RHI/Renderer.h"

using namespace SingularEngine;

RasterizationStateD3D11::RasterizationStateD3D11(const RasterizationStateDesc &desc) :
    RasterizationState(desc)
{
    D3D11_RASTERIZER_DESC rasterizerDesc = ConvertDesc(desc);
    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext());
    auto hr = context->mDevice->CreateRasterizerState(&rasterizerDesc, &mState);
    SINGULAR_ASSERT(SUCCEEDED(hr));
}

RasterizationStateD3D11::~RasterizationStateD3D11() {

    if (mState != nullptr) {
        mState->Release();
        mState = nullptr;
    }
}

D3D11_RASTERIZER_DESC RasterizationStateD3D11::ConvertDesc(const RasterizationStateDesc &desc) {

    D3D11_RASTERIZER_DESC rasterizerDesc;

    if (desc.fillMode == RasterizationFillMode::Solid) {
        rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    }
    else if (desc.fillMode == RasterizationFillMode::WireFrame) {
        rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    }
    else {
        SINGULAR_ASSERT(false);
    }

    if (desc.cullMode == RasterizationCullMode::None) {
        rasterizerDesc.CullMode = D3D11_CULL_NONE;
    }
    else if (desc.cullMode == RasterizationCullMode::Front) {
        rasterizerDesc.CullMode = D3D11_CULL_FRONT;
    }
    else if (desc.cullMode == RasterizationCullMode::Back) {
        rasterizerDesc.CullMode = D3D11_CULL_BACK;
    }
    else {
        SINGULAR_ASSERT(false);
    }

    rasterizerDesc.FrontCounterClockwise = desc.FrontCounterClockWise;

    rasterizerDesc.DepthBias = false;
    rasterizerDesc.DepthBiasClamp = 0;
    rasterizerDesc.SlopeScaledDepthBias = 0;
    rasterizerDesc.DepthClipEnable = true;
    rasterizerDesc.ScissorEnable = false;
    rasterizerDesc.MultisampleEnable = false;
    rasterizerDesc.AntialiasedLineEnable = false;

    return rasterizerDesc;
}
