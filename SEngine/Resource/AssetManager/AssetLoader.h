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

    public:
        static Assimp::Importer* MeshImporter;
    };
}