#include "MeshRenderComponent.h"
#include "Functional/RHI/Renderer.h"

using namespace SingularEngine;

void MeshRenderComponent::Initialize() {

    mConstantBufferPerObject = Renderer::Instance->CreateConstantBuffer(ConstantBufferDataType::PerObject, sizeof(ConstantBufferDataPerObject));
    mRenderItem = Renderer::Instance->CreateRenderItem(nullptr, mConstantBufferPerObject);
}

void MeshRenderComponent::Finalize() {

}

void MeshRenderComponent::Tick() {

    UpdateConstantBufferPerObject();
}

const RenderItem *MeshRenderComponent::GetRenderItem() {

    return mRenderItem.get();
}

void MeshRenderComponent::SetMesh(const std::shared_ptr<Mesh> &mesh) {

    mRenderItem->SetMesh(mesh);
    mRenderItem->AllocateMaterials(mesh->GetMaterialCount());
}

void MeshRenderComponent::SetMaterial(int index, const std::shared_ptr<Material> &material) {

    mRenderItem->SetMaterial(index, material);
}

int MeshRenderComponent::GetMaterialCount() const {

    return (int)mRenderItem->GetMaterialCount();
}

std::shared_ptr<Material> MeshRenderComponent::GetMaterial(int index) {

    return mRenderItem->GetMaterial(index);
}

void MeshRenderComponent::UpdateConstantBufferPerObject() {

    auto perObject = (ConstantBufferDataPerObject*)mConstantBufferPerObject->GetData();
    perObject->mWorldMatrix = GetOwner()->GetTransform()->GetRTSMatrix();
}
