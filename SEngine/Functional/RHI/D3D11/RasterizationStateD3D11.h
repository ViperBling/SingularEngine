#pragma once

#include <d3d11.h>

#include "Functional/RHI/RasterizationState.h"

namespace SingularEngine
{
    class RasterizationStateD3D11 : public RasterizationState
    {
    public:
        RasterizationStateD3D11(const RasterizationStateDesc& desc);
        ~RasterizationStateD3D11() override;

        ID3D11RasterizerState* GetInternalState() { return mState; }
        D3D11_RASTERIZER_DESC ConvertDesc(const RasterizationStateDesc& desc);

    private:
        ID3D11RasterizerState* mState = nullptr;
    };
}