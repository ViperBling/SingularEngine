#include "RenderItemD3D11.h"
#include "Core/Math/MathPCH.h"
#include "Functional/RHI/Renderer.h"

using namespace SingularEngine;

void RenderItemD3D11::Render() const {

}

void RenderItemD3D11::Render(const std::shared_ptr<Material> &overrideMat) const {

}

std::shared_ptr<RenderItemD3D11> RenderItemD3D11::Create(
    const std::shared_ptr<Mesh> &mesh,
    const std::vector<std::shared_ptr<Material>> &materials,
    const std::shared_ptr<ConstantBuffer> &perObject)
{
    return std::shared_ptr<RenderItemD3D11>();
}

std::shared_ptr<RenderItemD3D11> RenderItemD3D11::Create(
    const std::shared_ptr<Mesh> &mesh,
    const std::shared_ptr<ConstantBuffer> &perObject)
{
    return std::shared_ptr<RenderItemD3D11>();
}

void RenderItemD3D11::BindConstantBufferPerObject(RenderContextD3D11 *context) const {

    auto perObject = GetConstantBufferPerObject();
    if (perObject != nullptr) {
        GetConstantBufferPerObject()->Bind();
    }
}

void RenderItemD3D11::DrawMesh(
    RenderContextD3D11 *context,
    const std::shared_ptr<Material> &overrideMaterial) const
{
    auto mesh = GetMesh();

    for (const auto& subMesh : mesh->mSubMeshes) {

        if (overrideMaterial == nullptr) {
            auto material = GetMaterial(subMesh->GetMaterialIndex());

            if (material == nullptr) {

                Logger::Warning("material not found!");
            }
            else {

                if (material->GetMaterialType() == MaterialType::MeshRender) {
                    material->SetMatrix("ModelMatrix", subMesh->GetModelMatrix());
                }
                material->Apply();
            }
        }
        else {
            if (overrideMaterial->GetMaterialType() == MaterialType::ShadowMapping) {
                overrideMaterial->SetMatrix("ModelMatrix", subMesh->GetModelMatrix());
            }
            overrideMaterial->Apply();
        }

        // set up mesh data
        auto positionBuffer = subMesh->GetPositionBuffer();
        auto normalBuffer = subMesh->GetNormalBuffer();
        auto texcoordBuffer = subMesh->GetTexCoordBuffer();
        auto indexBuffer = subMesh->GetIndexBuffer();

        if (positionBuffer != nullptr)
        {
            UINT stride = positionBuffer->GetStride();
            UINT offset = positionBuffer->GetOffset();
            auto vb = std::dynamic_pointer_cast<VertexBufferD3D11>(positionBuffer);
            auto buffer = vb->GetBuffer();
            // https://docs.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-iasetvertexbuffers
            context->mDeviceContext->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
        }

        if (normalBuffer != nullptr)
        {
            UINT stride = normalBuffer->GetStride();
            UINT offset = normalBuffer->GetOffset();
            auto vb = std::dynamic_pointer_cast<VertexBufferD3D11>(normalBuffer);
            auto buffer = vb->GetBuffer();
            context->mDeviceContext->IASetVertexBuffers(1, 1, &buffer, &stride, &offset);
        }

        if (texcoordBuffer != nullptr)
        {
            UINT stride = texcoordBuffer->GetStride();
            UINT offset = texcoordBuffer->GetOffset();
            auto vb = std::dynamic_pointer_cast<VertexBufferD3D11>(texcoordBuffer);
            auto buffer = vb->GetBuffer();
            context->mDeviceContext->IASetVertexBuffers(2, 1, &buffer, &stride, &offset);
        }

        // https://docs.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-iasetprimitivetopology
        if (subMesh->GetPrimitiveType() == PrimitiveType::Triangle)
        {
            context->mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        }
        else if (subMesh->GetPrimitiveType() == PrimitiveType::Line)
        {
            context->mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
        }

        auto ib = std::dynamic_pointer_cast<IndexBufferD3D11>(indexBuffer);
        // https://docs.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-iasetindexbuffer
        context->mDeviceContext->IASetIndexBuffer(ib->GetBuffer(), ib->GetDXGIFormat(), 0);

        // https://docs.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-drawindexed
        context->mDeviceContext->DrawIndexed(ib->GetElementCount(), ib->GetStartIndex(), 0);
    }
}
