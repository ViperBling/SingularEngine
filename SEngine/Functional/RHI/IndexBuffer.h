#pragma once

#include "Platform/Assert.h"
#include "Functional/RHI/RenderBuffer.h"

namespace SingularEngine
{
    enum class IndexBufferFormat
    {
        UINT16,
        UINT32,
    };

    struct IndexBufferCreateParam
    {
        void* mIndexData;
        int mElementCount;
        IndexBufferFormat mFormat;
        int mStartIndex;

        IndexBufferCreateParam() :
            mIndexData(nullptr),
            mStartIndex(0),
            mFormat(IndexBufferFormat::UINT32),
            mElementCount(0)
        {}

        ~IndexBufferCreateParam() {

            if (mIndexData != nullptr) {
                delete [] mIndexData;
                mIndexData = nullptr;
            }
        }

        int GetFormatSize() const {
            switch (mFormat) {
                case IndexBufferFormat::UINT16 : return 2;
                case IndexBufferFormat::UINT32 : return 4;
                default:
                    SINGULAR_ASSERT(false);
                    return -1;
            }
        }
    };

    class IndexBuffer : public RenderBuffer
    {
    public:
        ~IndexBuffer() override = default;
    };
}