#pragma once

#include <memory>
#include <vector>
#include <array>

#include "Functional/Scene/RenderPass/RenderPassBase.h"
#include "Functional/GameObject/GameObject.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/RHI/RenderItem.h"
#include "Functional/RHI/RenderTarget.h"
#include "Functional/RHI/RasterizationState.h"

namespace SingularEngine
{
    class RenderPassMeshMaterial : public RenderPassBase
    {
    public:
        explicit RenderPassMeshMaterial(CreateRendererContextParam param);
        void Render(const std::shared_ptr<RasterizationState>& rs);
        void ResizeResolution(int width, int height) override;
        void SetShadowMap(const std::shared_ptr<RenderTarget>& shadowMap);

        const std::shared_ptr<RenderTarget>& GetMainRT() { return mMainRT; }

    private:
        void CollectRenderItems();
        void BuildRenderQueueVisitGameObject(GameObject* node);
        void CreateCoordAxisRenderItem();

    private:
        std::vector<RenderItem const*> mItems;
        std::vector<std::shared_ptr<RenderItem>> mAxisRenderItems;
        std::shared_ptr<RenderTarget> mMainRT = nullptr;
        std::shared_ptr<RenderTarget> mShadowMap = nullptr;
        bool mShowCoordAxis = true;
    };
}