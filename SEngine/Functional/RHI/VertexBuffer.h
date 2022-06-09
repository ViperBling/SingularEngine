#pragma once

#include <memory>

#include "Platform/Assert.h"
#include "Functional/RHI/RenderBuffer.h"

namespace SingularEngine
{
    enum class VertexBufferFormat
    {
        UnKnown = 0,
        F3,
        F4,
    };

    struct VertexBufferCreateParam
    {
        void* mVertexData;
        int mElementCount;
        VertexBufferFormat mFormat;

        int GetFormatStride() const {

            switch (mFormat) {
                case VertexBufferFormat::F3 : return sizeof(float) * 3;
                case VertexBufferFormat::F4 : return sizeof(float) * 4;
                default :
                    SINGULAR_ASSERT(false);
                    return -1;
            }
        }
    };

    class VertexBuffer : public RenderBuffer
    {
    public:
        VertexBuffer() = delete;
        virtual ~VertexBuffer(){}
        VertexBuffer(VertexBufferFormat vFormat, int count, int stride, int offset) :
            mFormat(vFormat),
            mElementCount(count),
            mStride(stride),
            mOffset(offset)
        {}

        VertexBufferFormat GetFormat() { return mFormat; }
        int GetElementCount() const { return mElementCount; }
        int GetStride() const { return mStride; }
        int GetOffset() const { return mOffset; }

    private:
        VertexBufferFormat mFormat;
        int mElementCount = 0;
        int mStride = 0;
        int mOffset = 0;
    };
}