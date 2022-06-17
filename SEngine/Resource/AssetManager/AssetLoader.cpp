#include <iostream>

#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "AssetLoader.h"
#include "Platform/Assert.h"
#include "Functional/RHI/Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "ThirdParty/Stb/stb_image.h"

using namespace SingularEngine;

Assimp::Importer* AssetLoader::MeshImporter = nullptr;

void AssetLoader::Init() {
    MeshImporter = new Assimp::Importer();
}

void AssetLoader::Finalize() {

    delete MeshImporter;
}

Matrix4x4f ConvertMatrix(const aiMatrix4x4 & matrix) {

    Matrix4x4f ret;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            ret[r][c] = matrix[r][c];
        }
    }
    return ret;
}

PrimitiveType ConvertPrimitiveType(unsigned int pt) {

    if (pt == aiPrimitiveType::aiPrimitiveType_POINT) {
        return PrimitiveType::Point;
    }
    else if (pt == aiPrimitiveType::aiPrimitiveType_LINE) {
        return PrimitiveType::Line;
    }
    else if (pt == aiPrimitiveType::aiPrimitiveType_TRIANGLE) {
        return PrimitiveType::Triangle;
    }
    else {
        SINGULAR_ASSERT(false);
        return PrimitiveType::Unknown;
    }
}

void Convert3ChanelTo4Chanel(const unsigned char* origin, unsigned char* target, int width, int height) {

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {

            int pixelIndex = r * width + c;
            target[pixelIndex * 4] = origin[pixelIndex * 3];
            target[pixelIndex * 4 + 1] = origin[pixelIndex * 3 + 1];
            target[pixelIndex * 4 + 2] = origin[pixelIndex * 3 + 2];
            target[pixelIndex * 4 + 3] = 255;
        }
    }
}

void VisitAssimpSceneNodeToLoadMesh(const aiScene* scene, const aiNode* node, aiMatrix4x4 parentTransform, const std::shared_ptr<MeshCreateParam>& param) {

    for (int i = 0; i < node->mNumMeshes; ++i) {

        auto meshNode = scene->mMeshes[node->mMeshes[i]];
        auto modelMatrix = parentTransform * node->mTransformation;
        auto subParam = std::make_shared<SubMeshCreateParam>();

        if (meshNode->HasPositions()) {
            subParam->mPositionCreateParam = std::make_shared<VertexBufferCreateParam>();
            subParam->mPositionCreateParam->mFormat = VertexBufferFormat::F3;
            subParam->mPositionCreateParam->mElementCount = (int)meshNode->mNumVertices;
            subParam->mPositionCreateParam->mVertexData = meshNode->mVertices;
        }

        if (meshNode->HasNormals()) {
            subParam->mNormalCreateParam = std::make_shared<VertexBufferCreateParam>();
            subParam->mNormalCreateParam->mFormat = VertexBufferFormat::F3;
            subParam->mNormalCreateParam->mElementCount = (int)meshNode->mNumVertices;
            subParam->mNormalCreateParam->mVertexData = meshNode->mNormals;
        }

        if (meshNode->HasTextureCoords(0)) {
            subParam->mTexCoordCreateParam = std::make_shared<VertexBufferCreateParam>();
            subParam->mTexCoordCreateParam->mFormat = VertexBufferFormat::F3;
            subParam->mTexCoordCreateParam->mElementCount = (int)meshNode->mNumVertices;
            subParam->mTexCoordCreateParam->mVertexData = meshNode->mTextureCoords[0];
        }

        subParam->mPrimitiveType = ConvertPrimitiveType(meshNode->mPrimitiveTypes);
        subParam->mIndexCreateParam = std::make_shared<IndexBufferCreateParam>();
        subParam->mIndexCreateParam->mFormat = IndexBufferFormat::UINT32;

        if (meshNode->mPrimitiveTypes == aiPrimitiveType::aiPrimitiveType_TRIANGLE) {

            int elementCount = (int)meshNode->mNumFaces * 3;
            subParam->mIndexCreateParam->mIndexData = new unsigned int[elementCount];
            subParam->mIndexCreateParam->mElementCount = elementCount;

            for (size_t j = 0; j < meshNode->mNumFaces; j++) {

                auto face = meshNode->mFaces[j];
                auto ptr = (unsigned int*)(subParam->mIndexCreateParam->mIndexData);
                ptr[j * 3] = face.mIndices[0];
                ptr[j * 3 + 1] = face.mIndices[1];
                ptr[j * 3 + 2] = face.mIndices[2];
            }
        }
        else {
            SINGULAR_ASSERT(false);
        }
        subParam->mMaterialIndex = (int)meshNode->mMaterialIndex;
        subParam->mModelMatrix = ConvertMatrix(modelMatrix);
        param->mSubMeshCreateParam.push_back(subParam);
    }

    for (int i = 0; i < node->mNumChildren; ++i) {
        auto child = node->mChildren[i];
        VisitAssimpSceneNodeToLoadMesh(scene, child, parentTransform * node->mTransformation, param);
    }
}

std::shared_ptr<MeshCreateParam> AssetLoader::LoadMesh(const std::string &path) {

    auto param = std::make_shared<MeshCreateParam>();
    auto readFlag = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType;
    readFlag = readFlag | aiProcess_ConvertToLeftHanded;

    auto sceneRoot = MeshImporter->ReadFile(path, readFlag);
    param->mRawResource = sceneRoot;
    param->mMaterialCount = (int)sceneRoot->mNumMaterials;
    SINGULAR_ASSERT(sceneRoot);

    VisitAssimpSceneNodeToLoadMesh(sceneRoot, sceneRoot->mRootNode, aiMatrix4x4(), param);

    return param;
}

std::shared_ptr<RawTexture> AssetLoader::LoadRawTexture(const std::string &path) {

    int iw, ih, n;
    unsigned char* data = stbi_load(path.c_str(), &iw, &ih, &n, 0);

    if (n == 4) {
        auto ret = std::make_shared<RawTexture>(iw, ih, RawTextureFormat::R8G8B8A8, data);
        stbi_image_free(data);
        return ret;
    }
    else if (n == 3) {
        int textureSize = iw * ih * 4;
        auto* textureData = new unsigned char[textureSize];
        Convert3ChanelTo4Chanel(data, textureData, iw, ih);
        auto ret = std::make_shared<RawTexture>(iw, ih, RawTextureFormat::R8G8B8A8, textureData);
        stbi_image_free(data);
        delete[] textureData;
        return ret;
    }
    else {
        SINGULAR_ASSERT(false);
        return nullptr;
    }
}
