#pragma once

#include <memory>
#include <d3d11.h>

#include "Functional/RHI/Texture.h"

namespace SingularEngine
{
    class TextureD3D11 : public ImageTexture
    {
    public:
        TextureD3D11() = delete;
        TextureD3D11(
            const std::shared_ptr<RawTexture>& rawImage,
            ID3D11Texture2D* texture2D,
            ID3D11ShaderResourceView* srv
            ) :
            ImageTexture(rawImage),
            mTexture(texture2D),
            mSRV(srv)
        {}

        ~TextureD3D11() override;

        ID3D11Texture2D* GetTexture() { return mTexture; }
        ID3D11ShaderResourceView* GetSRV() { return mSRV; }

    private:
        ID3D11Texture2D* mTexture;
        ID3D11ShaderResourceView* mSRV;

    public:
        static std::shared_ptr<TextureD3D11> Create(const std::shared_ptr<RawTexture>& rawTexture);
    };
}