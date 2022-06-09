#pragma once

#include <memory>
#include <assimp/Importer.hpp>

#include "Functional/RHI/Mesh.h"
#include "Functional/RHI/Texture.h"

namespace SingularEngine
{
    class AssetLoader
    {
    public:
        static void Init();
        static void Finalize();
        static std::shared_ptr<MeshCreateParam> LoadMesh(const std::string& path);
        static std::shared_ptr<RawTexture> LoadRawTexture(const std::string& path);

    public:
        static Assimp::Importer* MeshImporter;
    };
}