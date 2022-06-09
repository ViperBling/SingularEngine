#pragma once

#include <memory>
#include <array>

#include "Functional/Scene/RenderPass/RenderPassBase.h"
#include "Functional/RHI/Mesh.h"
#include "Functional/RHI/RenderTarget.h"
#include "Functional/RHI/RenderItem.h"

namespace SingularEngine
{
    enum class PostProcessEffect
    {
        None,
        Gray
    };

    class RenderPassPostProcess : public RenderPassBase
    {
    public:
        RenderPassPostProcess();
        void Render(const std::shared_ptr<RenderTarget>& inputRT, const std::shared_ptr<RenderTarget>& outputRT);

        PostProcessEffect GetPostProcessEffect() { return mEffect; }
        void SetPostProcessEffect(PostProcessEffect effect) { mEffect = effect; }

    private:
        void CreateRenderItem();
        void CreateMaterial();

    private:
        PostProcessEffect mEffect;
        std::shared_ptr<Material> mMaterialNone;
        std::shared_ptr<Material> mMaterialGray;
        std::shared_ptr<RenderItem> mRenderItem;
        std::shared_ptr<Mesh> mMesh;
        std::shared_ptr<ConstantBuffer> mConstantBuffer;
    };
}