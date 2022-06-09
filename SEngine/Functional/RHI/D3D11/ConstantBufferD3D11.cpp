#include "ConstantBufferD3D11.h"
#include "Platform/Assert.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/RHI/D3D11/RenderContextD3D11.h"

using namespace SingularEngine;


void ConstantBufferD3D11::Bind() {

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext()).get();
    // map data
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    auto result = context->mDeviceContext->Map(mConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    SINGULAR_ASSERT(SUCCEEDED(result));

    auto dataPtr = (void*)mappedResource.pData;
    memcpy(dataPtr, mData, mSize);
    context->mDeviceContext->Unmap(mConstantBuffer, 0);

    // todo: get startSlot from shader reflection without hardcode
    if (GetDataType() == ConstantBufferDataType::PerFrame)
    {
        context->mDeviceContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);
        context->mDeviceContext->PSSetConstantBuffers(0, 1, &mConstantBuffer);
    }
    else if(GetDataType() == ConstantBufferDataType::PerObject)
    {
        context->mDeviceContext->VSSetConstantBuffers(1, 1, &mConstantBuffer);
        context->mDeviceContext->PSSetConstantBuffers(1, 1, &mConstantBuffer);
    }
    else if(GetDataType() == ConstantBufferDataType::PerMaterial)
    {
        context->mDeviceContext->VSSetConstantBuffers(2, 1, &mConstantBuffer);
        context->mDeviceContext->PSSetConstantBuffers(2, 1, &mConstantBuffer);
    }
    else
    {
        SINGULAR_ASSERT(false);
    }
}

std::shared_ptr<ConstantBufferD3D11> ConstantBufferD3D11::Create(ConstantBufferDataType dt, int size) {

    ID3D11Buffer* cb;
    D3D11_BUFFER_DESC constantBufferDesc;
    // Set up the description of the dynamic matrix constant buffer that is in the vertex shader.
    constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    constantBufferDesc.ByteWidth = size;
    constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    constantBufferDesc.MiscFlags = 0;
    constantBufferDesc.StructureByteStride = 0;

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext());
    auto result = context->mDevice->CreateBuffer(&constantBufferDesc, nullptr, &cb);
    SINGULAR_ASSERT(SUCCEEDED(result));

    return std::make_shared<ConstantBufferD3D11>(dt, size, cb);
}
