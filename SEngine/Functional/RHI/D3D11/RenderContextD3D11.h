#pragma once

#include <memory>
#include <d3d11.h>

#include "Functional/RHI/RenderContext.h"
#include "Functional/RHI/D3D11/RenderTargetD3D11.h"

namespace SingularEngine
{
    class RenderContextD3D11 : public RenderContext
    {
    public:
        RenderContextD3D11() = delete;
        RenderContextD3D11(
            ID3D11Device* device,
            ID3D11DeviceContext* deviceContext,
            IDXGISwapChain* swapChain,
            std::shared_ptr<RenderTargetD3D11> mainRT
            ) :
            mDevice(device),
            mDeviceContext(deviceContext),
            mSwapChain(swapChain),
            mMainRT(mainRT)
        {}

        virtual ~RenderContextD3D11() override {

            if (mSwapChain != nullptr) {
                mSwapChain->Release();
                mSwapChain = nullptr;
            }

            if (mDeviceContext != nullptr) {
                mDeviceContext->Release();
                mDeviceContext = nullptr;
            }

            if (mDevice != nullptr) {
                mDevice->Release();
                mDevice = nullptr;
            }
        }

    public:
        ID3D11Device* mDevice;
        ID3D11DeviceContext* mDeviceContext;
        IDXGISwapChain* mSwapChain;
        std::shared_ptr<RenderTargetD3D11> mMainRT;
    };
}