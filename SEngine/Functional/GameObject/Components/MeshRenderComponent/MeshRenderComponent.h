#pragma once

#include <memory>
#include <string>

#include "Functional/RHI/Mesh.h"
#include "Functional/RHI/Shader.h"
#include "Functional/RHI/RenderItem.h"
#include "Functional/GameObject/GameObject.h"
#include "Functional/GameObject/Components/Component.h"

namespace SingularEngine
{
    class MeshRenderComponent : public Component
    {
    public:
        MeshRenderComponent() = delete;
        explicit MeshRenderComponent(GameObject* owner) : Component(owner) {}

        ~MeshRenderComponent() override = default;

        void Initialize() override;
        void Finalize() override;
        void Tick() override;

    public:
        const RenderItem* GetRenderItem();
        void SetMesh(const std::shared_ptr<Mesh>& mesh);
        void SetMaterial(int index, const std::shared_ptr<Material>& material);
        int GetMaterialCount() const;
        std::shared_ptr<Material> GetMaterial(int index);

        bool& GetCastShadowFlag() {return mCastShadow; }
        void SetCastShadowFlag(bool flag) { mCastShadow = flag; }

    private:
        void UpdateConstantBufferPerObject();


    private:
        std::shared_ptr<RenderItem> mRenderItem = nullptr;
        std::shared_ptr<ConstantBuffer> mConstantBufferPerObject = nullptr;
        bool mCastShadow = true;
    };
}