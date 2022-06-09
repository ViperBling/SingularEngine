#pragma once

#include <memory>
#include <d3d11.h>

#include "Functional/RHI/VertexBuffer.h"

namespace SingularEngine
{
    class VertexBufferD3D11 : public VertexBuffer
    {
    public:
        VertexBufferD3D11() = delete;
        VertexBufferD3D11(ID3D11Buffer* buffer, VertexBufferFormat vFormat, int count, int stride, int offset) :
            VertexBuffer(vFormat, count, stride, offset),
            mBuffer(buffer)
        {}

        virtual ~VertexBufferD3D11() {

            if (mBuffer != nullptr) {
                mBuffer->Release();
                mBuffer = nullptr;
            }
        }

        ID3D11Buffer* GetBuffer() { return mBuffer; }



    private:
        ID3D11Buffer* mBuffer;

    public:
        static std::shared_ptr<VertexBufferD3D11> Create(std::shared_ptr<VertexBufferCreateParam> param);

    };
}