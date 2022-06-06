#pragma once

#include <memory>
#include <utility>

#include "Functional/RHI/Material.h"

namespace SingularEngine
{
    enum class RawTextureFormat
    {
        R8G8B8A8,
        R8G8B8,
    };

    enum class TextureType
    {
        ImageTexture,
        RTTexture,
    };

    class RawTexture
    {
    public:
        explicit RawTexture(int width, int height, RawTextureFormat rFormat, void* data);
        virtual ~RawTexture();

        int GetWidth() const { return mWidth; }
        int GetHeight() const { return mHeight; }
        RawTextureFormat GetFormat() const { return mFormat; }
        int GetPixelBytes();
        void* GetData() { return mData; }

    private:
        int mWidth = 0;
        int mHeight = 0;
        RawTextureFormat mFormat;
        unsigned char* mData;
    };

    class Texture
    {
    public:
        explicit Texture(TextureType tt) : mTextureType(tt) {}
        virtual ~Texture() = default;

        TextureType GetTextureType() { return mTextureType; }

    private:
        TextureType mTextureType;
    };

    class ImageTexture : public Texture
    {
    public:
        explicit ImageTexture(const std::shared_ptr<RawTexture>&  rawTexture) :
            Texture(TextureType::ImageTexture),
            mWidth(rawTexture->GetWidth()),
            mHeight(rawTexture->GetHeight()),
            mFormat(rawTexture->GetFormat())
        {}

        int GetWidth() const { return mWidth; }
        int GetHeight() const { return mHeight; }
        RawTextureFormat GetFormat() const { return mFormat; }

        int GetPixelBytes();

    private:
        int mWidth;
        int mHeight;
        RawTextureFormat mFormat;
    };

    class RTTexture : public Texture
    {
    public:
        RTTexture() : Texture(TextureType::RTTexture) {}
        virtual void Bind() = 0;
    };
}