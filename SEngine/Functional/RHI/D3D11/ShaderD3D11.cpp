#include <d3dcompiler.h>
#include <iostream>

#include "ShaderD3D11.h"
#include "Platform/Assert.h"
#include "Functional/RHI/D3D11/RendererD3D11.h"
#include "Functional/RHI/D3D11/RenderContextD3D11.h"

using namespace SingularEngine;

std::shared_ptr<VertexShaderD3D11> VertexShaderD3D11::Create(const std::string &path) {

    HRESULT hr;
    ID3DBlob* errorMessage;
    ID3DBlob* byteCode;
    ID3D11VertexShader* vs;
    ID3D11InputLayout* layout;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
    dwShaderFlags |= D3DCOMPILE_DEBUG;
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

    std::wstring _path = std::wstring(path.begin(), path.end());
    hr = D3DCompileFromFile(
        _path.c_str(), nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main", "vs_5_0",
        dwShaderFlags, 0, &byteCode, &errorMessage);
    if (FAILED(hr)) {
        OutputDebugString(reinterpret_cast<const char*>(errorMessage->GetBufferPointer()));
        std::cout << reinterpret_cast<const char*>(errorMessage->GetBufferPointer()) << std::endl;
    }
    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext());
    context->mDevice->CreateVertexShader(byteCode->GetBufferPointer(), byteCode->GetBufferSize(), nullptr, &vs);

    SINGULAR_ASSERT(SUCCEEDED(hr));

    D3D11_INPUT_ELEMENT_DESC ied[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    context->mDevice->CreateInputLayout(ied, 3, byteCode->GetBufferPointer(), byteCode->GetBufferSize(), &layout);
    if (layout == nullptr) SINGULAR_ASSERT(false);

    return std::make_shared<VertexShaderD3D11>(vs, layout, byteCode);
}

void VertexShaderD3D11::Bind() {

    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext());
    context->mDeviceContext->IASetInputLayout(mLayout);
    context->mDeviceContext->VSSetShader(mVS, nullptr, 0);
}

std::shared_ptr<PixelShaderD3D11> PixelShaderD3D11::Create(const std::string &path) {

    HRESULT hr;
    ID3DBlob* errorMessage;
    ID3DBlob* byteCode;
    ID3D11PixelShader* ps;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
    dwShaderFlags |= D3DCOMPILE_DEBUG;
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

    std::wstring _path = std::wstring(path.begin(), path.end());
    hr = D3DCompileFromFile(
        _path.c_str(), nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main", "ps_5_0",
        dwShaderFlags, 0, &byteCode, &errorMessage);

    if (FAILED(hr)) {
        OutputDebugString(reinterpret_cast<const char*>(errorMessage->GetBufferPointer()));
        std::cout << reinterpret_cast<const char*>(errorMessage->GetBufferPointer()) << std::endl;
    }
    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext());
    context->mDevice->CreatePixelShader(byteCode->GetBufferPointer(), byteCode->GetBufferSize(), nullptr, &ps);

    SINGULAR_ASSERT(SUCCEEDED(hr));

    return std::make_shared<PixelShaderD3D11>(ps, byteCode);
}

void PixelShaderD3D11::Bind() {
    auto context = std::dynamic_pointer_cast<RenderContextD3D11>(Renderer::Instance->GetContext());
    context->mDeviceContext->PSSetShader(mPS, 0, 0);
}


