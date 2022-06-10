#include <imgui.h>
#include <memory>

#include "GamePanel.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/Scene/RenderPass/RenderPassManager.h"
#include "Functional/Scene/SceneManager.h"
#include "Platform/Assert.h"
#include "Platform/Platform.h"

#ifdef SINGULAR_PLATFORM_WINDOWS
#include "Functional/RHI/D3D11/RenderTargetD3D11.h"
#endif

#pragma warning(disable : 4312)

using namespace SingularEngine;

static bool first = true;

const char* Resolutions[] = {"1920x1080", "1280x720", "960x540"};
const char* PostProcessEffects[] = {"None", "Gray"};
const char* RasterizationEffect[] = {"Default", "WireFrame"};

void GamePanel::Initialize() {

    RasterizationStateDesc desc{};
    desc.cullMode = RasterizationCullMode::Back;
    desc.fillMode = RasterizationFillMode::WireFrame;
    desc.FrontCounterClockWise =false;
    mWireFrameRS = Renderer::Instance->CreateRasterizationState(desc);
}

void GamePanel::Render() {

    if (first) {
        first = false;
        return;
    }

    ImGui::Begin("Game Window", &mbShowing);
    ImGui::PushItemWidth(100);
    RenderResolutionOptions();
    ImGui::SameLine();
    RenderPostProcessOptions();
    ImGui::SameLine();
    RenderRasterizationStateOptions();
    ImGui::PopItemWidth();
    RenderSceneToRT();
    RenderRTTOWindow();
    ImGui::End();
}

void GamePanel::Finalize() {

}

void GamePanel::RenderResolutionOptions() {

    ImGui::Combo("Resolution", &mSelectedResolution, Resolutions, IM_ARRAYSIZE(Resolutions), IM_ARRAYSIZE(Resolutions));
    if (mSelectedResolution == 0) {
        mTargetResolutionWidth = 1920;
        mTargetResolutionHeight = 1080;
    }
    else if (mSelectedResolution == 1) {
        mTargetResolutionWidth = 1280;
        mTargetResolutionHeight = 720;
    }
    else if (mSelectedResolution == 2) {
        mTargetResolutionWidth = 960;
        mTargetResolutionHeight = 540;
    }
    else {
        Logger::Error("unknown resolution!");
        SINGULAR_ASSERT(false);
    }

    if (mRT == nullptr || mSelectedResolution != mLastRasterization) {
        ResizeRT();
        SceneManager::Instance->GetMainCamera()->SetAspectRatio((float)mTargetResolutionWidth / (float)mTargetResolutionHeight);
        mLastResolution = mSelectedResolution;
    }
}

void GamePanel::RenderPostProcessOptions() {

    int cur = (int)RenderPassManager::Instance->GetPostProcessEffect();
    ImGui::Combo("PostProcess", &cur, PostProcessEffects, IM_ARRAYSIZE(PostProcessEffects), IM_ARRAYSIZE(PostProcessEffects));
    RenderPassManager::Instance->SetPostProcessEffect((PostProcessEffect)cur);
}

void GamePanel::RenderRasterizationStateOptions() {

    ImGui::Combo("Rasterization", &mLastRasterization, RasterizationEffect, IM_ARRAYSIZE(RasterizationEffect), IM_ARRAYSIZE(RasterizationEffect));
}

void GamePanel::ResizeRT() {

    if (mRT == nullptr) {
        RenderTargetDesc desc{};
        desc.rtUsage = RenderTargetUsage::Default;
        desc.width = mTargetResolutionWidth;
        desc.height = mTargetResolutionHeight;
        mRT = Renderer::Instance->CreateRenderTarget(desc);
    }
    else {
        mRT->Resize(mTargetResolutionWidth, mTargetResolutionHeight);
    }
}

void GamePanel::RenderSceneToRT() {

    Renderer::Instance->SetViewPort(0, 0, mTargetResolutionWidth, mTargetResolutionHeight);

    if (mLastRasterization == 0) {
        SceneManager::Instance->Render(mRT, nullptr);
    }
    else if (mLastRasterization == 1) {
        SceneManager::Instance->Render(mRT, mWireFrameRS);
    }
    else {
        SINGULAR_ASSERT(false);
    }
}

void GamePanel::RenderRTTOWindow() {

    float optionHeight = 20;
    ImVec2 vMin = ImGui::GetWindowContentRegionMin();
    ImVec2 vMax = ImGui::GetWindowContentRegionMax();

    auto winWidth = (vMax.x - vMin.x);
    auto winHeight = (vMax.y - vMin.y) - optionHeight;

    float warpWidth, warpHeight;

    if ((float)mTargetResolutionWidth / (float)mTargetResolutionHeight > winWidth / winHeight) {

        warpWidth = (float)winWidth * 0.95f;
        warpHeight = (float)winWidth * (float)mTargetResolutionHeight / (float)mTargetResolutionWidth * 0.95f;
    }
    else
    {
        warpWidth = (float)winHeight * (float)mTargetResolutionWidth / (float)mTargetResolutionHeight * 0.95f;
        warpHeight = (float)winHeight * 0.95f;
    }

    ImGui::SetCursorPosX((float)winWidth / 2 - warpWidth / 2 + 10);
    ImGui::SetCursorPosY((float)(vMax.y - vMin.y) / 2 - warpHeight / 2 + optionHeight * 2);
    ImVec2 winSize = {warpWidth, warpHeight};

    if (Renderer::Instance->mAPIType == RenderAPI::OpenGL)
    {
//        auto rt = std::dynamic_pointer_cast<OpenglRenderTarget>(m_RT);
//        auto tid = reinterpret_cast<ImTextureID>(rt->GetTexture());
//        // https://github.com/cinder/Cinder/issues/2185
//        ImVec2 uv0 = {0, 1};
//        ImVec2 uv1 = {1, 0};
//        ImGui::Image(tid, winSize, uv0, uv1);
    }

    else if (Renderer::Instance->mAPIType == RenderAPI::D3D11) {

#ifdef SINGULAR_PLATFORM_WINDOWS
        auto rt = std::dynamic_pointer_cast<RenderTargetD3D11>(mRT);
        auto tid = (ImTextureID)rt->GetSRV();
        ImGui::Image(tid, winSize);
#endif
    }
    else {
        SINGULAR_ASSERT(false);
    }
}
