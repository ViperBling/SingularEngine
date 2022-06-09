#pragma once

#include <memory>

#include "Functional/Scene/RenderPass/RenderPassMeshMaterial.h"
#include "Functional/Scene/RenderPass/RenderPassShadowMap.h"
#include "Functional/Scene/RenderPass/RenderPassPostProcess.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/RHI/RenderTarget.h"

namespace SingularEngine
{
    class RenderPassManager
    {
    public:
        RenderPassManager() = default;
        ~RenderPassManager();

        void Init(CreateRendererContextParam param);

    public:
        void RenderShadowMap();
        void RenderMeshMaterials(const std::shared_ptr<RasterizationState>& rs);
        void RenderPostProcess(const std::shared_ptr<RenderTarget>& rt);
        void ResizeResolution(int width, int height);

        PostProcessEffect GetPostProcessEffect() { return mRenderPassPostProcess->GetPostProcessEffect(); }
        void SetPostProcessEffect(PostProcessEffect effect);

    public:
        static RenderPassManager* Instance;

    private:
        RenderPassMeshMaterial* mRenderPassMeshMaterial = nullptr;
        RenderPassShadowMap* mRenderPassShadowMap = nullptr;
        RenderPassPostProcess* mRenderPassPostProcess = nullptr;
    };
}