#pragma once

#include <memory>
#include <d3d11.h>

#include "Functional/RHI/ConstantBuffer.h"

namespace SingularEngine
{
    class ConstantBufferD3D11 : public ConstantBuffer
    {
    public:
        ConstantBufferD3D11() = delete;
        explicit ConstantBufferD3D11(ConstantBufferDataType dt, int size, ID3D11Buffer* cbuffer) :
            ConstantBuffer(dt, size),
            mConstantBuffer(cbuffer)
        {}

        ~ConstantBufferD3D11() override {
            if (mConstantBuffer != nullptr) {
                mConstantBuffer->Release();
                mConstantBuffer = nullptr;
            }
        }

        ID3D11Buffer* GetBuffer() { return mConstantBuffer; }

        void Bind() override;

    private:
        ID3D11Buffer* mConstantBuffer = nullptr;

    public:
        static std::shared_ptr<ConstantBufferD3D11> Create(ConstantBufferDataType dt, int size);
    };
}