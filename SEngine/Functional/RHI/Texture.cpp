#include "Texture.h"

using namespace SingularEngine;


RawTexture::RawTexture(int width, int height, RawTextureFormat rFormat, void *data) :
    mWidth(width),
    mHeight(height),
    mFormat(rFormat)
{
    int dataSize = width * height * GetPixelBytes();
    mData = (unsigned char*)malloc(dataSize);
    memcpy(mData, data, dataSize);
}

RawTexture::~RawTexture() {

    delete [] mData;
    mData = nullptr;
}

int RawTexture::GetPixelBytes() {

    switch (mFormat) {
        case RawTextureFormat::R8G8B8A8 : return 4;
        case RawTextureFormat::R8G8B8 : return 3;
        default:
            SINGULAR_ASSERT(false);
            return -1;
    }
}


int ImageTexture::GetPixelBytes() {

    switch (mFormat) {
        case RawTextureFormat::R8G8B8A8 : return 4;
        case RawTextureFormat::R8G8B8 : return 3;
        default:
            SINGULAR_ASSERT(false);
            return -1;
    }
}