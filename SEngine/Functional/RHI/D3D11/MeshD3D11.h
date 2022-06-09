#pragma once

#include <vector>
#include <memory>

#include "Functional/RHI/Mesh.h"
#include "Functional/RHI/D3D11/IndexBufferD3D11.h"
#include "Functional/RHI/D3D11/VertexBufferD3D11.h"
#include "Core/Logging/Logger.h"

namespace SingularEngine
{
    class SubMeshD3D11 : public SubMesh
    {
    public:
        SubMeshD3D11() = delete;
        SubMeshD3D11(
            std::shared_ptr<VertexBuffer>& position,
            std::shared_ptr<VertexBuffer>& normal,
            std::shared_ptr<VertexBuffer>& texcoord,
            std::shared_ptr<IndexBuffer>& index,
            const std::shared_ptr<SubMeshCreateParam>& param) :
            SubMesh(position, normal, texcoord, index, param)
        {}

        ~SubMeshD3D11() override = default;

    public:
        static std::shared_ptr<SubMeshD3D11> Create(std::shared_ptr<SubMeshCreateParam> param);
    };

    class MeshD3D11 : public Mesh
    {
    public:
        explicit MeshD3D11(const std::shared_ptr<MeshCreateParam>& param) :
            Mesh(param->mMaterialCount)
        {}

        ~MeshD3D11() override = default;

    public:
        static std::shared_ptr<MeshD3D11> Create(std::shared_ptr<MeshCreateParam> param);
    };
}