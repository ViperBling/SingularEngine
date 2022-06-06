#pragma once

#include "Functional/RHI/Texture.h"

namespace SingularEngine
{
    enum class RenderTargetUsage
    {
        Default,
        ShadowMap,
    };

    struct RenderTargetDesc
    {
        RenderTargetUsage rtUsage;
        int width;
        int height;
    };

    class RenderTarget : public RTTexture
    {
    public:
        RenderTarget() = delete;

        explicit RenderTarget(RenderTargetDesc rtDesc) :
            RTTexture(),
            mDesc(rtDesc)
        {}

        ~RenderTarget() override = default;
        virtual void Resize(int width, int height);
        int GetWidth() const { return mDesc.width; }
        int GetHeight() const { return mDesc.height; }

    protected:
        RenderTargetDesc mDesc;
    };
}