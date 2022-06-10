#pragma once

#include <memory>

#include "Functional/RHI/RenderTarget.h"
#include "Functional/RHI/RasterizationState.h"
#include "PanelBase.h"
#include "Functional/GameObject/GameObject.h"

namespace SingularEngine
{
    class GamePanel : public PanelBase
    {
    public:
        GamePanel() : mRT(nullptr) {}

        void Initialize() override;
        void Render() override;
        void Finalize() override;

    private:
        void RenderResolutionOptions();
        void RenderPostProcessOptions();
        void RenderRasterizationStateOptions();
        void ResizeRT();
        void RenderSceneToRT();
        void RenderRTTOWindow();

    private:
        int mSelectedResolution = 0;
        int mLastResolution = 0;
        int mLastRasterization= 0;
        int mTargetResolutionWidth = 0;
        int mTargetResolutionHeight = 0;

        std::shared_ptr<RenderTarget> mRT;
        std::shared_ptr<RasterizationState> mWireFrameRS;
    };
}

