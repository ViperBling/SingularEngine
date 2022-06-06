#pragma once

#include <memory>
#include <utility>

#include "Functional/RHI/ConstantBuffer.h"
#include "Functional/RHI/IndexBuffer.h"
#include "Functional/RHI/Material.h"
#include "Functional/RHI/Mesh.h"
#include "Functional/RHI/Shader.h"
#include "Functional/RHI/VertexBuffer.h"


namespace SingularEngine
{
    class RenderItem
    {
    public:

        RenderItem() = delete;
        RenderItem(
            const std::shared_ptr<Mesh>& mesh,
            std::vector<std::shared_ptr<Material>> materials,
            const std::shared_ptr<ConstantBuffer>& perObject
            )
        {
            mMesh = mesh;
            mMaterials = std::move(materials);
            mConstantBufferPerObject = perObject;
        }

        RenderItem(
            const std::shared_ptr<Mesh>& mesh,
            const std::shared_ptr<ConstantBuffer>& perObject
            )
        {
            mMesh = mesh;
            mConstantBufferPerObject = perObject;
        }

        virtual ~RenderItem() = default;

        std::shared_ptr<Mesh> GetMesh() const { return mMesh; }
        std::shared_ptr<ConstantBuffer> GetConstantBufferPerObject() const { return mConstantBufferPerObject; }

        void SetMesh(const std::shared_ptr<Mesh>& mesh) { mMesh = mesh; }
        void SetConstantBuffer(const std::shared_ptr<ConstantBuffer>& cb) { mConstantBufferPerObject = cb; }

        void AllocateMaterials(int count);
        std::shared_ptr<Material> GetMaterial(int index) const;
        void SetMaterial(int index, const std::shared_ptr<Material>& material);
        size_t GetMaterialCount() const;

        virtual void Render() const = 0;
        virtual void Render(const std::shared_ptr<Material>& material) const = 0;

    protected:
        std::shared_ptr<Mesh> mMesh;
        std::vector<std::shared_ptr<Material>> mMaterials;
        std::shared_ptr<ConstantBuffer> mConstantBufferPerObject;
    };
}

