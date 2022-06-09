#include "MeshD3D11.h"

using namespace SingularEngine;

std::shared_ptr<SubMeshD3D11> SubMeshD3D11::Create(const std::shared_ptr<SubMeshCreateParam> param) {

    std::shared_ptr<VertexBuffer> position = nullptr;
    std::shared_ptr<VertexBuffer> normal = nullptr;
    std::shared_ptr<VertexBuffer> texcoord = nullptr;
    std::shared_ptr<IndexBuffer>  index = nullptr;

    if (param->mPositionCreateParam != nullptr)
    {
        position = VertexBufferD3D11::Create(param->mPositionCreateParam);
    }

    if (param->mNormalCreateParam != nullptr)
    {
        normal = VertexBufferD3D11::Create(param->mNormalCreateParam);
    }

    if (param->mTexCoordCreateParam != nullptr)
    {
        texcoord = VertexBufferD3D11::Create(param->mTexCoordCreateParam);
    }

    if (param->mIndexCreateParam != nullptr)
    {
        index = IndexBufferD3D11::Create(param->mIndexCreateParam);
    }
    return std::make_shared<SubMeshD3D11>(position, normal, texcoord, index, param);
}


std::shared_ptr<MeshD3D11> MeshD3D11::Create(const std::shared_ptr<MeshCreateParam> param) {

    auto mesh = std::make_shared<MeshD3D11>(param);

    for (size_t i = 0; i < param->GetSubMeshCount(); i++) {
        auto sub = SubMeshD3D11::Create(param->mSubMeshCreateParam[i]);
        mesh->mSubMeshes.emplace_back(sub);
    }
    return mesh;
}

