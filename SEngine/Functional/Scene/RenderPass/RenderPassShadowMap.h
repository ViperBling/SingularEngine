#pragma once

#include <vector>
#include <memory>

#include "Functional/Scene/RenderPass/RenderPassBase.h"
#include "Functional/RHI/RenderItem.h"
#include "Functional/RHI/RenderTarget.h"
#include "Functional/GameObject/GameObject.h"

namespace SingularEngine
{
    class RenderPassShadowMap : public RenderPassBase
    {
    public:
        RenderPassShadowMap();
        void Render();
        const std::shared_ptr<RenderTarget>& GetShadowMap() { return mShadowMap; }

    private:
        void InitShadowMapRT();
        void InitShadowMapMaterial();
        void CollectRenderItems();
        void BuildRenderQueueVisitGameObject(GameObject* node);

    private:
        std::vector<RenderItem const*> mItems;
        std::shared_ptr<RenderTarget> mShadowMap = nullptr;
        std::shared_ptr<Material> mShadowMapMaterial = nullptr;
    };
}