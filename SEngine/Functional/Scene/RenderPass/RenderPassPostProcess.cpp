#include "RenderPassPostProcess.h"
#include "Core/Math/MathPCH.h"
#include "Functional/RHI/Renderer.h"

using namespace SingularEngine;


RenderPassPostProcess::RenderPassPostProcess() :
    mEffect(PostProcessEffect::None)
{
    CreateMaterial();
    CreateRenderItem();
}

void RenderPassPostProcess::Render(
    const std::shared_ptr<RenderTarget> &inputRT,
    const std::shared_ptr<RenderTarget> &outputRT)
{
    Renderer::Instance->SetRenderTarget(outputRT);
    Renderer::Instance->ClearRenderTarget(outputRT, 0.1f, 0.1f, 0.1f, 1.0f);
    Renderer::Instance->SetRasterizationState(nullptr);

    if (outputRT != nullptr) {
        Renderer::Instance->SetViewPort(0, 0, outputRT->GetWidth(), outputRT->GetHeight());
    }
    else {
        Renderer::Instance->SetViewPort(0, 0, -1, -1);
    }

    if (mEffect == PostProcessEffect::None) {
        mMaterialNone->SetTexture("MainTex", inputRT);
        mRenderItem->Render(mMaterialNone);
    }
    else {
        mMaterialGray->SetTexture("MainTex", inputRT);
        mRenderItem->Render(mMaterialGray);
    }
}

void RenderPassPostProcess::CreateRenderItem() {

    Vector3f positionData[4] = {
        {-1, -1, 0},
        {-1,  1, 0},
        {1,  -1, 0},
        {1,   1, 0}
    };

    // D3D Texture Coordinate
    // (0, 0)
    // |------------|
    // |            |
    // |            |
    // |            |
    // |------------| (1, 1)
    Vector3f TexCoordDataLeft[4] = {
        {0, 1, 0},
        {0, 0, 0},
        {1, 1, 0},
        {1, 0, 0}
    };

    // OpenGL Texture Coordinate
    // |------------| (1, 1)
    // |            |
    // |            |
    // |            |
    // |------------|
    // (0, 0)
    Vector3f TexCoordDataRight[4] = {
        {0, 0, 0},
        {0, 1, 0},
        {1, 0, 0},
        {1, 1, 0}
    };

    unsigned int* indexDataLeft = new unsigned int[6] {0, 1, 2, 2, 1, 3};

    auto param = std::make_shared<MeshCreateParam>();
    auto subParam = std::make_shared<SubMeshCreateParam>();
    subParam->mPositionCreateParam = std::make_shared<VertexBufferCreateParam>();
    subParam->mPositionCreateParam->mElementCount = 4;
    subParam->mPositionCreateParam->mFormat = VertexBufferFormat::F3;
    subParam->mPositionCreateParam->mVertexData = positionData;

    subParam->mTexCoordCreateParam = std::make_shared<VertexBufferCreateParam>();
    subParam->mTexCoordCreateParam->mElementCount = 4;
    subParam->mTexCoordCreateParam->mFormat = VertexBufferFormat::F3;

    subParam->mIndexCreateParam = std::make_shared<IndexBufferCreateParam>();
    subParam->mIndexCreateParam->mElementCount = 6;
    subParam->mIndexCreateParam->mFormat = IndexBufferFormat::UINT32;
    subParam->mIndexCreateParam->mIndexData = indexDataLeft;

    if (Renderer::Instance->GetRenderAPI() == RenderAPI::D3D11) {
        subParam->mTexCoordCreateParam->mVertexData = TexCoordDataLeft;
    }
    else {
        subParam->mTexCoordCreateParam->mVertexData = TexCoordDataRight;
    }

    delete [] indexDataLeft;

    subParam->mPrimitiveType = PrimitiveType::Triangle;

    param->mSubMeshCreateParam.emplace_back(subParam);
    mMesh = Renderer::Instance->CreateMesh(param);
    mConstantBuffer = Renderer::Instance->CreateConstantBuffer(ConstantBufferDataType::PerObject, sizeof(ConstantBufferDataPerObject));
    mRenderItem = Renderer::Instance->CreateRenderItem(mMesh, mConstantBuffer);
}

void RenderPassPostProcess::CreateMaterial() {

    mMaterialNone = Renderer::Instance->CreateMaterial("GlobalPostProcessNone", MaterialType::PostProcess);
    mMaterialGray = Renderer::Instance->CreateMaterial("GlobalPostProcessGray", MaterialType::PostProcess);
}
