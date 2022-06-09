#include "VertexBufferD3D11.h"
#include "Platform/Assert.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/RHI/D3D11/RenderContextD3D11.h"

using namespace SingularEngine;

std::shared_ptr<VertexBufferD3D11> VertexBufferD3D11::Create(std::shared_ptr<VertexBufferCreateParam> param) {

    HRESULT hr;
    ID3D11Buffer* buffer;

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext());
    auto sizeInBytes = param->mElementCount * param->GetFormatStride();

    // create vertex buffer
    {
        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(bufferDesc));

        bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufferDesc.ByteWidth = sizeInBytes;
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        bufferDesc.MiscFlags = 0;
        bufferDesc.StructureByteStride = 0;

        hr = context->mDevice->CreateBuffer(&bufferDesc, nullptr, &buffer);
        SINGULAR_ASSERT(SUCCEEDED(hr));

    }
    // copy data
    {
        D3D11_MAPPED_SUBRESOURCE mappedSubresource;
        hr = context->mDeviceContext->Map(buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubresource);
        SINGULAR_ASSERT(SUCCEEDED(hr));
        memcpy(mappedSubresource.pData, param->mVertexData, sizeInBytes);
        context->mDeviceContext->Unmap(buffer, NULL);
    }

    return std::make_shared<VertexBufferD3D11>(buffer, param->mFormat, param->mElementCount, param->GetFormatStride(), 0);
}
