#pragma once

#include <memory>
#include <d3d11.h>

#include "Functional/RHI/DepthStencilState.h"

namespace SingularEngine
{
    class DepthStencilStateD3D11 : public DepthStencilState
    {
    public:
        DepthStencilStateD3D11();
        ~DepthStencilStateD3D11() override;

        void Bind() override;

    private:
        void RebuildState();

    private:
        ID3D11DepthStencilState* mState;
    };
}