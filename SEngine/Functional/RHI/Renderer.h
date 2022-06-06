#pragma once

#include <memory>
#include <string>

#include "Functional/RHI/ConstantBuffer.h"
#include "Functional/RHI/DepthStencilState.h"
#include "Functional/RHI/Material.h"
#include "Functional/RHI/Mesh.h"
#include "Functional/RHI/RasterizationState.h"
#include "Functional/RHI/RenderContext.h"
#include "Functional/RHI/RenderItem.h"
#include "Functional/RHI/RenderTarget.h"
#include "Functional/RHI/Shader.h"
#include "Functional/RHI/Texture.h"

#include "Core/Interface/IModule.h"
#include "Platform/Platform.h"

namespace SingularEngine
{
    struct CreateRendererContextParam
    {
        int mResolutionWidth;
        int mResolutionHeight;
#ifdef SINGULAR_PLATFORM_WINDOWS
        HWND mHWND;
#endif
    };

    class Renderer
    {
    public:
        Renderer();
        virtual ~Renderer() = default;
        std::shared_ptr<RenderContext> GetContext();
        RenderAPI GetRenderAPI() const;

    public:
        virtual void Initialize(CreateRendererContextParam param) = 0;
        virtual void Finalize() = 0;
        virtual void ResizeResolution(int width, int height) = 0;
        virtual void SetViewPort(int x, int y, int w, int h) = 0;
        virtual void Present() = 0;
        virtual void ClearRenderTarget(std::shared_ptr<RenderTarget> rt, float r, float g, float b, float a) = 0;
        virtual void CreateDeviceContext() = 0;
        virtual void ReleaseDeviceContext() = 0;
        virtual void SetRenderTarget(const std::shared_ptr<RenderTarget>& rt) = 0;
        virtual void SetRasterizationState(const std::shared_ptr<RasterizationState>& rs) = 0;
        virtual std::shared_ptr<Mesh> CreateMesh(const std::string& path) = 0;
        virtual std::shared_ptr<Mesh> CreateMesh(const std::shared_ptr<MeshCreateParam>& param) = 0;
        virtual std::shared_ptr<RenderTarget> CreateRenderTarget(RenderTargetDesc desc) = 0;
        virtual std::shared_ptr<Shader> CreateShader(const std::string& path, ShaderType shaderType) = 0;
        virtual std::shared_ptr<Material> CreateMaterial(const std::string& materialPath, MaterialType mt) = 0;
        virtual std::shared_ptr<DepthStencilState> CreateDepthStencilState() = 0;
        virtual std::shared_ptr<RenderItem> CreateRenderItem(const std::shared_ptr<Mesh>& mesh, const std::vector<std::shared_ptr<Material>>& materials, const std::shared_ptr<ConstantBuffer>& perObject) = 0;
        virtual std::shared_ptr<RenderItem> CreateRenderItem(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<ConstantBuffer>& perObject) = 0;
        virtual std::shared_ptr<ConstantBuffer> CreateConstantBuffer(ConstantBufferDataType dt, int size) = 0;
        virtual std::shared_ptr<Texture> CreateTexture(const std::string& path) = 0;
        virtual std::shared_ptr<RasterizationState> CreateRasterizationState(const RasterizationStateDesc& desc) = 0;

    protected:
        void CreateDefaultRasterizationState();

    public:
        RenderAPI mAPIType;
        int mResolutionWidth = 0;
        int mResolutionHeight = 0;
#ifdef SINGULAR_PLATFORM_WINDOWS
        HWND mHWND {};
#endif
        static Renderer* Instance;

    protected:
        std::shared_ptr<RenderContext> mContext = nullptr;
        std::shared_ptr<RasterizationState> mDefaultRasterizationState = nullptr;
    };
}
