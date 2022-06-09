#pragma once

#include <iostream>
#include <memory>
#include <d3d11.h>

#include "Functional/RHI/RenderTarget.h"

namespace SingularEngine
{
    class RenderTargetD3D11 : public RenderTarget
    {
    public:
        explicit RenderTargetD3D11(RenderTargetDesc rtDesc, ID3D11Device* device);
        explicit RenderTargetD3D11(RenderTargetDesc rtDesc, ID3D11Device* device, IDXGISwapChain* swapChain);
        ~RenderTargetD3D11() override;

        void Resize(int width, int height) override;
        void Bind() override;

        ID3D11RenderTargetView* GetRenderTargetView() { return mRenderTargetView; }
        ID3D11DepthStencilView* GetDepthStencilView() { return mDepthStencilView; }
        ID3D11ShaderResourceView* GetSRV() { return mShaderResourceView; }
        ID3D11ShaderResourceView* GetDepthSRV() { return mDepthStencilSRV; }

    private:
        void ClearRenderTarget();
        void ClearDepthStencilResource();

        void CreateRenderTarget(RenderTargetDesc rtDesc, ID3D11Device* device);
        void CreateRenderTargetFromSwapChain(RenderTargetDesc rtDesc, ID3D11Device* device, IDXGISwapChain* swapChain);
        void CreateDepthStencilResource(RenderTargetDesc rtDesc, ID3D11Device* device);

    private:
        ID3D11Texture2D* mRenderTargetTexture = nullptr;
        ID3D11RenderTargetView* mRenderTargetView = nullptr;
        ID3D11ShaderResourceView* mShaderResourceView = nullptr;
        ID3D11Texture2D* mDepthStencilTexture = nullptr;
        ID3D11DepthStencilView* mDepthStencilView = nullptr;
        ID3D11ShaderResourceView* mDepthStencilSRV = nullptr;

    public:
        static std::shared_ptr<RenderTargetD3D11> CreateFromSwapChain(RenderTargetDesc rtDesc, ID3D11Device* device, IDXGISwapChain* swapChain);
        static std::shared_ptr<RenderTargetD3D11> Create(RenderTargetDesc rtDesc, ID3D11Device* device);
    };
}