#include "IndexBufferD3D11.h"
#include "Platform/Assert.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/RHI/D3D11/RenderContextD3D11.h"

using namespace SingularEngine;

DXGI_FORMAT IndexBufferD3D11::GetDXGIFormat() {

    if (mFormat == IndexBufferFormat::UINT16) {
        return DXGI_FORMAT_R16_UINT;
    }
    else if (mFormat == IndexBufferFormat::UINT32) {
        return DXGI_FORMAT_R32_UINT;
    }
    else {
        SINGULAR_ASSERT(false);
        return DXGI_FORMAT_UNKNOWN;
    }
}

std::shared_ptr<IndexBufferD3D11> IndexBufferD3D11::Create(std::shared_ptr<IndexBufferCreateParam> param) {

    ID3D11Buffer* buffer;
    D3D11_BUFFER_DESC indexBufferDesc;
    D3D11_SUBRESOURCE_DATA indexData;

    // Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = param->mElementCount * param->GetFormatSize();
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the index data.
    indexData.pSysMem = param->mIndexData;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    HRESULT hr;
    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext());
    hr = context->mDevice->CreateBuffer(&indexBufferDesc, &indexData, &buffer);
    SINGULAR_ASSERT(SUCCEEDED(hr));

    auto indexBuffer = std::make_shared<IndexBufferD3D11>(buffer, param);

    return indexBuffer;
}
