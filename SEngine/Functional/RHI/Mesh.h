#pragma once

#include <memory>
#include <vector>

#include <assimp/scene.h>

#include "Functional/RHI/IndexBuffer.h"
#include "Functional/RHI/VertexBuffer.h"
#include "Core/Math/MathPCH.h"
#include "Core/Logging/Logger.h"

namespace SingularEngine
{
    enum class PrimitiveType
    {
        Unknown = 0,
        Point,
        Line,
        Triangle,
    };

    struct SubMeshCreateParam
    {
        std::shared_ptr<VertexBufferCreateParam> mPositionCreateParam;
        std::shared_ptr<VertexBufferCreateParam> mNormalCreateParam;
        std::shared_ptr<VertexBufferCreateParam> mTexCoordCreateParam;
        std::shared_ptr<VertexBufferCreateParam> mIndexCreateParam;

        PrimitiveType mPrimitiveType;
        int mMaterialIndex;
        Matrix4x4f mModelMatrix;

        SubMeshCreateParam() :
            mPositionCreateParam(nullptr),
            mNormalCreateParam(nullptr),
            mTexCoordCreateParam(nullptr),
            mIndexCreateParam(nullptr),
            mPrimitiveType(PrimitiveType::Unknown),
            mMaterialIndex(-1),
            mModelMatrix()
        {}
    };

    struct MeshCreateParam
    {
        const aiScene* mRawResource;
        int mMaterialCount;
        std::vector<std::shared_ptr<SubMeshCreateParam>> mSubMeshCreateParam;

        MeshCreateParam() :
            mRawResource(nullptr),
            mMaterialCount(0)
        {}

        size_t GetSubMeshCount() const {
            return mSubMeshCreateParam.size();
        }
    };

    class SubMesh
    {
    public:
        SubMesh() = delete;
        SubMesh(
            std::shared_ptr<VertexBuffer>& position,
            std::shared_ptr<VertexBuffer>& normal,
            std::shared_ptr<VertexBuffer>& texcoord,
            std::shared_ptr<IndexBuffer>& index,
            const std::shared_ptr<SubMeshCreateParam>& param
            ) :
            mPositionBuffer(position),
            mNormalBuffer(normal),
            mTexCoordBuffer(texcoord),
            mIndexBuffer(index),
            mPrimitiveType(param->mPrimitiveType),
            mMaterialIndex(param->mMaterialIndex),
            mModelMatrix(param->mModelMatrix)
        {}

        virtual ~SubMesh() = default;

        std::shared_ptr<VertexBuffer> GetPositionBuffer() {
            return mPositionBuffer;
        }

        std::shared_ptr<VertexBuffer> GetNormalBuffer() {
            return mNormalBuffer;
        }

        std::shared_ptr<VertexBuffer> GetTexCoordBuffer() {
            return mTexCoordBuffer;
        }

        std::shared_ptr<IndexBuffer> GetIndexBuffer() {
            return mIndexBuffer;
        }

        int GetMaterialIndex() const
        {
            return mMaterialIndex;
        }

        Matrix4x4f GetModelMatrix() const
        {
            return mModelMatrix;
        }

        PrimitiveType GetPrimitiveType() const { return mPrimitiveType; }

    protected:
        std::shared_ptr<VertexBuffer> mPositionBuffer = nullptr;
        std::shared_ptr<VertexBuffer> mNormalBuffer = nullptr;
        std::shared_ptr<VertexBuffer> mTexCoordBuffer = nullptr;
        std::shared_ptr<IndexBuffer> mIndexBuffer = nullptr;
        PrimitiveType mPrimitiveType = PrimitiveType::Unknown;
        int mMaterialIndex;
        Matrix4x4f mModelMatrix;
    };

    class Mesh
    {
    public:
        explicit Mesh(int materialCount) :
            mMaterialCount(materialCount)
        {}

        virtual ~Mesh() = default;

        int GetMaterialCount() const { return mMaterialCount; }

    public:
        std::vector<std::shared_ptr<SubMesh>> mSubMeshes;
        int mMaterialCount;
    };
}
