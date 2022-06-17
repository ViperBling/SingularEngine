#include "RenderPassMeshMaterial.h"
#include "Functional/Scene/SceneManager.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/GameObject/Components/MeshRenderComponent/MeshRenderComponent.h"

using namespace SingularEngine;


RenderPassMeshMaterial::RenderPassMeshMaterial(CreateRendererContextParam param) {

    RenderTargetDesc desc{};
    desc.rtUsage = RenderTargetUsage::Default;
    desc.width = param.mResolutionWidth;
    desc.height = param.mResolutionHeight;
    mMainRT = Renderer::Instance->CreateRenderTarget(desc);
//    CreateCoordAxisRenderItem();
}

void RenderPassMeshMaterial::Render(const std::shared_ptr<RasterizationState> &rs) {

    SceneManager::Instance->GetConstantBufferPerScene()->Bind();
    Renderer::Instance->SetRenderTarget(mMainRT);
    Renderer::Instance->ClearRenderTarget(mMainRT, 0.1f, 0.1f, 0.1f, 1.0f);
    Renderer::Instance->SetRasterizationState(rs);
    Renderer::Instance->SetViewPort(0, 0, mMainRT->GetWidth(), mMainRT->GetHeight());

    CollectRenderItems();
    for (auto item : mItems) {
        item->Render();
    }
    if (mShowCoordAxis) {
        for (const auto & item : mAxisRenderItems) {
            item->Render();
        }
    }
}

void RenderPassMeshMaterial::ResizeResolution(int width, int height) {

    mMainRT->Resize(width, height);
}

void RenderPassMeshMaterial::SetShadowMap(const std::shared_ptr<RenderTarget> &shadowMap) {

    mShadowMap = shadowMap;
    if (mShadowMap != nullptr) {
        mShadowMap->Bind();
    }
}

void RenderPassMeshMaterial::CollectRenderItems() {

    mItems.clear();
    auto root = SceneManager::Instance->GetRoot();
    BuildRenderQueueVisitGameObject(root.get());
}

void RenderPassMeshMaterial::BuildRenderQueueVisitGameObject(GameObject *node) {

    auto meshRender = node->GetComponent<MeshRenderComponent>();
    if (meshRender != nullptr) {
        mItems.emplace_back(meshRender->GetRenderItem());
    }
    for (auto & child : node->GetTransform()->GetChildren()) {
        BuildRenderQueueVisitGameObject(child->GetOwner());
    }
}

void RenderPassMeshMaterial::CreateCoordAxisRenderItem() {

    Vector3f pointsLeftHand[12] =
        {
            {0, 0, 0}, {2000, 0, 0},
            {0, 0, 0}, {-2000, 0, 0},
            {0, 0, 0}, {0, 2000, 0},
            {0, 0, 0}, {0, -2000, 0},
            {0, 0, 0}, {0, 0, 2000},
            {0, 0, 0}, {0, 0, -2000}
        };

    Vector4f colors[6] =
        {
            {1, 0, 0, 1},
            {0.5, 0, 0, 1},
            {0, 1, 0, 1},
            {0, 0.5, 0, 1},
            {0, 0, 1, 1},
            {0, 0, 0.5, 1}
        };

    auto vbp = std::make_shared<VertexBufferCreateParam>();
    vbp->mFormat = VertexBufferFormat::F3;
    vbp->mElementCount = 12;
    vbp->mVertexData = pointsLeftHand;


    unsigned int** indices = new unsigned int* [6];

    auto mp = std::make_shared<MeshCreateParam>();
    for (int i = 0; i < 6; i++) {

        indices[i] = new unsigned int[2];
        indices[i][0] = i * 2;
        indices[i][1] = i * 2 + 1;

        auto ibp = std::make_shared<IndexBufferCreateParam>();
        ibp->mStartIndex = 0;
        ibp->mFormat = IndexBufferFormat::UINT32;
        ibp->mElementCount = 2;
        ibp->mIndexData = indices[i];

        auto smp = std::make_shared<SubMeshCreateParam>();
        smp->mPositionCreateParam = vbp;
        smp->mIndexCreateParam = ibp;
        smp->mMaterialIndex = i;
        smp->mPrimitiveType = PrimitiveType::Line;
        mp->mSubMeshCreateParam.emplace_back(smp);
    }

    auto mesh = Renderer::Instance->CreateMesh(mp);
    auto item = Renderer::Instance->CreateRenderItem(mesh, nullptr);
    item->AllocateMaterials(6);

    for (int i = 0; i < 6; i++) {
        auto material = Renderer::Instance->CreateMaterial("ColorAxis", MaterialType::MeshRender);
        material->SetVector4("BaseColor", colors[i]);
        item->SetMaterial(i, material);
    }

    mAxisRenderItems.emplace_back(item);
    delete [] indices;
}
