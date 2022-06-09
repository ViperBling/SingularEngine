#pragma once

#include <d3d11.h>
#include <memory>
#include <iostream>

#include "Functional/RHI/Shader.h"

namespace SingularEngine
{
    class VertexShaderD3D11 : public Shader
    {
    public:
        VertexShaderD3D11() = delete;
        VertexShaderD3D11(ID3D11VertexShader* vs, ID3D11InputLayout* layout, ID3DBlob* bytecode) :
            Shader(ShaderType::VertexShader),
            mVS(vs),
            mLayout(layout),
            mByteCode(bytecode)
        {}

        ~VertexShaderD3D11() override {

            if (mByteCode != nullptr) {
                mByteCode->Release();
                mByteCode = nullptr;
            }
            if (mVS != nullptr) {
                mVS->Release();
                mVS = nullptr;
            }
            if (mLayout != nullptr) {
                mLayout->Release();
                mLayout = nullptr;
            }
        }

        ID3D11VertexShader* GetShader() { return mVS; }
        ID3D11InputLayout* GetLayout() { return mLayout; }

        void Bind() override;

    private:
        ID3D11VertexShader* mVS;
        ID3D11InputLayout* mLayout;
        ID3DBlob* mByteCode;

    public:
        static std::shared_ptr<VertexShaderD3D11> Create(const std::string& path);
    };

    class PixelShaderD3D11 : public Shader
    {
    public:
        explicit PixelShaderD3D11(ID3D11PixelShader* ps, ID3DBlob* bytecode) :
            Shader(ShaderType::PixelShader),
            mPS(ps),
            mByteCode(bytecode)
        {}

        ~PixelShaderD3D11() override {

            if (mByteCode != nullptr) {
                mByteCode->Release();
                mByteCode = nullptr;
            }
            if (mPS != nullptr) {
                mPS->Release();
                mPS = nullptr;
            }
        }

        ID3D11PixelShader* GetShader() { return mPS; }

        void Bind() override;

    private:
        ID3D11PixelShader* mPS = nullptr;
        ID3DBlob* mByteCode;

    public:
        static std::shared_ptr<PixelShaderD3D11> Create(const std::string& path);
    };
}