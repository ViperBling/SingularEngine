#include "AssetLoader.h"

using namespace SingularEngine;

void AssetLoader::Init() {
    MeshImporter = new Assimp::Importer();
}

void AssetLoader::Finalize() {

    delete MeshImporter;
}
