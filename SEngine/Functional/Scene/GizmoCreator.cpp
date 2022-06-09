#include "GizmoCreator.h"
#include "Functional/RHI/Renderer.h"

using namespace SingularEngine;


std::shared_ptr<Mesh> GizmoCreator::CreatePlane() {

    Vector3f positionData[4] =
        {
            {1.0f, 0.0f, 1.0f},
            {1.0f, 0.0f, -1.0f},
            {-1.0f, 0.0f, -1.0f},
            {-1.0f, 0.0f, 1.0f},
        };

    Vector3f normalData[4] =
        {
            {0.0f, 1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f}
        };

    std::array<unsigned int, 6> indexData {0, 1, 2, 0, 2, 3};

    auto param = std::make_shared<MeshCreateParam>();
    auto subParam = std::make_shared<SubMeshCreateParam>();
    subParam->mModelMatrix = Matrix4x4f::Identity();
    subParam->mMaterialIndex = 0;
    subParam->mPrimitiveType = PrimitiveType::Triangle;

    subParam->mPositionCreateParam = std::make_shared<VertexBufferCreateParam>();
    subParam->mPositionCreateParam->mFormat = VertexBufferFormat::F3;
    subParam->mPositionCreateParam->mElementCount = 4;
    subParam->mPositionCreateParam->mVertexData = positionData;

    subParam->mNormalCreateParam = std::make_shared<VertexBufferCreateParam>();
    subParam->mNormalCreateParam->mFormat = VertexBufferFormat::F3;
    subParam->mNormalCreateParam->mElementCount = 4;
    subParam->mNormalCreateParam->mVertexData = normalData;

    subParam->mIndexCreateParam = std::make_shared<IndexBufferCreateParam>();
    subParam->mIndexCreateParam->mElementCount = 6;
    subParam->mIndexCreateParam->mFormat = IndexBufferFormat::UINT32;
    subParam->mIndexCreateParam->mStartIndex = 0;
    subParam->mIndexCreateParam->mIndexData = indexData.data();

    param->mSubMeshCreateParam.push_back(subParam);
    param->mMaterialCount = 1;
    auto mesh = Renderer::Instance->CreateMesh(param);
    return mesh;
}

std::shared_ptr<Mesh> GizmoCreator::CreateCube() {

    Vector3f positionData[24] =
        {
            // top
            {0.5f, 0.5f, 0.5f},
            {0.5f, 0.5f, -0.5f},
            {-0.5f, 0.5f, -0.5f},
            {-0.5f, 0.5f, 0.5f},
            // bottom
            {0.5f, -0.5f, 0.5f},
            {0.5f, -0.5f, -0.5f},
            {-0.5f, -0.5f, -0.5f},
            {-0.5f, -0.5f, 0.5f},
            // left
            {-0.5f, 0.5f, 0.5f},
            {-0.5f, -0.5f, 0.5f},
            {-0.5f, -0.5f, -0.5f},
            {-0.5f, 0.5f, -0.5f},
            // right
            {0.5f, 0.5f, 0.5f},
            {0.5f, -0.5f, 0.5f},
            {0.5f, -0.5f, -0.5f},
            {0.5f, 0.5f, -0.5f},
            // front
            {-0.5f, 0.5f, -0.5f},
            {0.5f, 0.5f, -0.5f},
            {0.5f, -0.5f, -0.5f},
            {-0.5f, -0.5f, -0.5f},
            // back
            {-0.5f, 0.5f, 0.5f},
            {0.5f, 0.5f, 0.5f},
            {0.5f, -0.5f, 0.5f},
            {-0.5f, -0.5f, 0.5f},

        };

    Vector3f normalData[24] =
        {
            // top
            {0.0f, 1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            // bottom
            {0.0f, -1.0f, 0.0f},
            {0.0f, -1.0f, 0.0f},
            {0.0f, -1.0f, 0.0f},
            {0.0f, -1.0f, 0.0f},
            // left
            {-1.0f, 0.0f, 0.0f},
            {-1.0f, 0.0f, 0.0f},
            {-1.0f, 0.0f, 0.0f},
            {-1.0f, 0.0f, 0.0f},
            // right
            {1.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            // front
            {0.0f, 0.0f, -1.0f},
            {0.0f, 0.0f, -1.0f},
            {0.0f, 0.0f, -1.0f},
            {0.0f, 0.0f, -1.0f},
            // back
            {0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 1.0f},
        };

    std::array<unsigned int, 36> indexData {
        0, 1, 2, 0, 2, 3, 4, 6, 5, 4, 7, 6,
        8, 11, 10, 8, 10, 9, 12, 14, 15, 12, 13, 14,
        16, 17, 18, 16, 18, 19, 20, 22, 21, 20, 23, 22
    };

    auto param = std::make_shared<MeshCreateParam>();
    auto subParam = std::make_shared<SubMeshCreateParam>();
    subParam->mModelMatrix = Matrix4x4f::Identity();
    subParam->mMaterialIndex = 0;
    subParam->mPrimitiveType = PrimitiveType::Triangle;

    subParam->mPositionCreateParam = std::make_shared<VertexBufferCreateParam>();
    subParam->mPositionCreateParam->mFormat = VertexBufferFormat::F3;
    subParam->mPositionCreateParam->mElementCount = 24;
    subParam->mPositionCreateParam->mVertexData = positionData;

    subParam->mNormalCreateParam = std::make_shared<VertexBufferCreateParam>();
    subParam->mNormalCreateParam->mFormat = VertexBufferFormat::F3;
    subParam->mNormalCreateParam->mElementCount = 24;
    subParam->mNormalCreateParam->mVertexData = normalData;

    subParam->mIndexCreateParam = std::make_shared<IndexBufferCreateParam>();
    subParam->mIndexCreateParam->mElementCount = 36;
    subParam->mIndexCreateParam->mFormat = IndexBufferFormat::UINT32;
    subParam->mIndexCreateParam->mStartIndex = 0;
    subParam->mIndexCreateParam->mIndexData = indexData.data();

    param->mSubMeshCreateParam.push_back(subParam);
    param->mMaterialCount = 1;
    auto mesh = Renderer::Instance->CreateMesh(param);
    return mesh;
}
