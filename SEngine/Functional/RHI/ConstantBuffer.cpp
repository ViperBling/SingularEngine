#include "ConstantBuffer.h"
#include "Platform/Assert.h"

using namespace SingularEngine;


ConstantBuffer::ConstantBuffer(ConstantBufferDataType cbDataType, int size) :
    mDataType(cbDataType)
{
    if (ConstantBufferDataType::PerObject == cbDataType) {
        mData = new ConstantBufferDataPerObject();
        mSize = sizeof(ConstantBufferDataPerObject);
    }
    else if (ConstantBufferDataType::PerFrame == cbDataType) {
        mData = new ConstantBufferDataPerFrame();
        mSize = sizeof(ConstantBufferDataPerFrame);
    }
    else {
        mData = new char[size];
        mSize = size;
    }

}

ConstantBuffer::~ConstantBuffer() {

    if (mData != nullptr) {

        if (ConstantBufferDataType::PerObject == mDataType) {
            auto data = (ConstantBufferDataPerObject*)mData;
            delete data;
        }
        else if(ConstantBufferDataType::PerFrame == mDataType) {
            auto data = (ConstantBufferDataPerFrame*)mData;
            delete data;
        }
        else if (ConstantBufferDataType::PerMaterial == mDataType) {
            auto data = (char*)mData;
            delete[] data;
        }
        else {
            SINGULAR_ASSERT(false);
        }
        mData = nullptr;
    }
}
