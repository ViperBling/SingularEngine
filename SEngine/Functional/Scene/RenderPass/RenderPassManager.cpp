#include "RenderPassManager.h"
#include "Functional/RHI/Renderer.h"

using namespace SingularEngine;

RenderPassManager* RenderPassManager::Instance = nullptr;

RenderPassManager::~RenderPassManager() {

    delete mRenderPassMeshMaterial;
    mRenderPassMeshMaterial = nullptr;

    delete mRenderPassShadowMap;
    mRenderPassShadowMap = nullptr;

    delete mRenderPassPostProcess;
    mRenderPassPostProcess = nullptr;
}

void RenderPassManager::Init(CreateRendererContextParam param) {

    mRenderPassShadowMap = new RenderPassShadowMap();
    mRenderPassMeshMaterial = new RenderPassMeshMaterial(param);
    mRenderPassPostProcess = new RenderPassPostProcess();
}

void RenderPassManager::RenderShadowMap() {

    mRenderPassShadowMap->Render();
}

void RenderPassManager::RenderMeshMaterials(const std::shared_ptr<RasterizationState> &rs) {

    SINGULAR_ASSERT(mRenderPassMeshMaterial != nullptr);
    auto shadowMap = mRenderPassShadowMap->GetShadowMap();
    mRenderPassMeshMaterial->SetShadowMap(shadowMap);
    mRenderPassMeshMaterial->Render(rs);
}

void RenderPassManager::RenderPostProcess(const std::shared_ptr<RenderTarget> &rt) {

    auto input = mRenderPassMeshMaterial->GetMainRT();
    mRenderPassPostProcess->Render(input, rt);
}

void RenderPassManager::ResizeResolution(int width, int height) {

    mRenderPassMeshMaterial->ResizeResolution(width, height);
    mRenderPassPostProcess->ResizeResolution(width, height);
}

void RenderPassManager::SetPostProcessEffect(PostProcessEffect effect) {

    mRenderPassPostProcess->SetPostProcessEffect(effect);
}

