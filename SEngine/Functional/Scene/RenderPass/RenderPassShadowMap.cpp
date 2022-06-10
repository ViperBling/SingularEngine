#include "RenderPassShadowMap.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/Scene/SceneManager.h"
#include "Functional/GameObject/Components/MeshRenderComponent/MeshRenderComponent.h"

using namespace SingularEngine;

const int SHADOW_MAP_WIDTH = 2048;
const int SHADOW_MAP_HEIGHT = 2048;


RenderPassShadowMap::RenderPassShadowMap() {

    InitShadowMapRT();
    InitShadowMapMaterial();
}

void RenderPassShadowMap::Render() {

    SceneManager::Instance->GetConstantBufferPerScene()->Bind();
    Renderer::Instance->SetRenderTarget(mShadowMap);
    Renderer::Instance->ClearRenderTarget(mShadowMap, 0.1f, 0.1f, 0.1f, 1.0f);
    Renderer::Instance->SetViewPort(0, 0, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);

    CollectRenderItems();

    for (auto item : mItems) {
        item->Render(mShadowMapMaterial);
    }
    // unbind shadow map so next render pass can use it as input texture
    Renderer::Instance->SetRenderTarget(nullptr);
}

void RenderPassShadowMap::InitShadowMapRT() {

    RenderTargetDesc desc{};

    desc.rtUsage = RenderTargetUsage::ShadowMap;
    desc.width = SHADOW_MAP_WIDTH;
    desc.height = SHADOW_MAP_HEIGHT;

    mShadowMap = Renderer::Instance->CreateRenderTarget(desc);
}

void RenderPassShadowMap::InitShadowMapMaterial() {

    mShadowMapMaterial = Renderer::Instance->CreateMaterial("GlobalShadowMapping", MaterialType::ShadowMapping);
}

void RenderPassShadowMap::CollectRenderItems() {

    mItems.clear();
    auto root = SceneManager::Instance->GetRoot();
    BuildRenderQueueVisitGameObject(root.get());
}

void RenderPassShadowMap::BuildRenderQueueVisitGameObject(GameObject *node) {

    auto meshRender = node->GetComponent<MeshRenderComponent>();

    if (meshRender != nullptr && meshRender->GetCastShadowFlag()) {
        mItems.emplace_back(meshRender->GetRenderItem());
    }

    for (auto& child : node->GetTransform()->GetChildren()) {
        BuildRenderQueueVisitGameObject(child->GetOwner());
    }
}
