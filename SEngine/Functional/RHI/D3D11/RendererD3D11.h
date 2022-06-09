#pragma once

#include <d3d11.h>

#include "Functional/RHI/Renderer.h"

namespace SingularEngine
{
    class RendererD3D11 : public Renderer
    {
        RendererD3D11() {}
        ~RendererD3D11() override = default;

        void CreateDeviceContext() override;
        void ReleaseDeviceContext() override;

        virtual void Initialize(CreateRendererContextParam param) override;
        virtual void Finalize() override;
        virtual void ResizeResolution(int width, int height) override;
        virtual void SetViewPort(int x, int y, int w, int h) override;
        virtual void Present() override;
        virtual void ClearRenderTarget(std::shared_ptr<RenderTarget> rt, float r, float g, float b, float a) override;
        virtual void SetRenderTarget(const std::shared_ptr<RenderTarget>& rt) override;
        virtual void SetRasterizationState(const std::shared_ptr<RasterizationState>& rs) override;

        virtual std::shared_ptr<Mesh> CreateMesh(const std::string& path) override;
        virtual std::shared_ptr<Mesh> CreateMesh(const std::shared_ptr<MeshCreateParam>& param) override;
        virtual std::shared_ptr<RenderTarget> CreateRenderTarget(RenderTargetDesc desc) override;
        virtual std::shared_ptr<Shader> CreateShader(const std::string& path, ShaderType shaderType) override;
        virtual std::shared_ptr<Material> CreateMaterial(const std::string& materialPath, MaterialType mt) override;
        virtual std::shared_ptr<DepthStencilState> CreateDepthStencilState() override;
        virtual std::shared_ptr<RenderItem> CreateRenderItem(const std::shared_ptr<Mesh>& mesh, const std::vector<std::shared_ptr<Material>>& materials, const std::shared_ptr<ConstantBuffer>& perObject) override;
        virtual std::shared_ptr<RenderItem> CreateRenderItem(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<ConstantBuffer>& perObject) override;
        virtual std::shared_ptr<ConstantBuffer> CreateConstantBuffer(ConstantBufferDataType dt, int size) override;
        virtual std::shared_ptr<Texture> CreateTexture(const std::string& path) override;
        virtual std::shared_ptr<RasterizationState> CreateRasterizationState(const RasterizationStateDesc& desc) override;
    };
}