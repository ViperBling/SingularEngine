#pragma once

#include <memory>
#include <d3d11.h>

#include "Functional/RHI/IndexBuffer.h"

namespace SingularEngine
{
    class IndexBufferD3D11 : public IndexBuffer
    {
    public:
        IndexBufferD3D11() = delete;
        IndexBufferD3D11(ID3D11Buffer* buffer, const std::shared_ptr<IndexBufferCreateParam>& param) :
            mIndexBuffer(buffer),
            mElementCount(param->mElementCount),
            mFormat(param->mFormat),
            mStartIndex(param->mStartIndex)
        {}

        virtual ~IndexBufferD3D11() {
            if (mIndexBuffer != nullptr) {
                mIndexBuffer->Release();
                mIndexBuffer = nullptr;
            }
        }

        ID3D11Buffer* GetBuffer() { return mIndexBuffer; }
        int GetElementCount() const { return mElementCount; }
        int GetStartIndex() const { return mStartIndex; }

        DXGI_FORMAT GetDXGIFormat();

    private:
        ID3D11Buffer* mIndexBuffer = nullptr;
        int mElementCount = 0;
        int mStartIndex = 0;
        IndexBufferFormat mFormat;

    public:
        static std::shared_ptr<IndexBufferD3D11> Create(std::shared_ptr<IndexBufferCreateParam> param);
    };
}