#include "DepthStencilStateD3D11.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/RHI/D3D11/RenderContextD3D11.h"

using namespace SingularEngine;

DepthStencilStateD3D11::DepthStencilStateD3D11() :
    mState(nullptr)
{

}

DepthStencilStateD3D11::~DepthStencilStateD3D11() {

    if (mState != nullptr) {
        mState->Release();
        mState = nullptr;
    }
}

void DepthStencilStateD3D11::Bind() {

    if (mbDirty) RebuildState();

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext());
    context->mDeviceContext->OMSetDepthStencilState(mState, 1);
}

void DepthStencilStateD3D11::RebuildState() {

    if (mState != nullptr) {
        mState->Release();
        mState = nullptr;
    }

    D3D11_DEPTH_STENCIL_DESC dsDesc;
    // Depth
    dsDesc.DepthEnable = mbDepthEnable;
    dsDesc.DepthWriteMask = static_cast<D3D11_DEPTH_WRITE_MASK>(mDepthWriteMask);
    dsDesc.DepthFunc = static_cast<D3D11_COMPARISON_FUNC>(mDepthComparisonFunc);
    // Stencil test parameters
    dsDesc.StencilEnable = mbStencilEnable;
    dsDesc.StencilReadMask = 0xFF;
    dsDesc.StencilWriteMask = 0xFF;

    // Stencil operations if pixel is front-facing
    dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    // Stencil operations if pixel is back-facing
    dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    // Create depth stencil state
    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext()).get();
    context->mDevice->CreateDepthStencilState(&dsDesc, &mState);
    mbDirty = false;
}
