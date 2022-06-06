#include <utility>

#include "Material.h"
#include "Functional/RHI/Renderer.h"

using namespace SingularEngine;

Material::Material(const std::string &materialName, MaterialType materialType) :
    mMaterialType(materialType),
    mMaterialName(materialName)
{
    if (Renderer::Instance->mAPIType == RenderAPI::D3D11) {

        std::string generatedDir(R"(Assets/Shaders/Generated/D3D11/)");
        std::string target = generatedDir + materialName + "_VS.hlsl";
        mVS = Renderer::Instance->CreateShader(target, ShaderType::VertexShader);
        target = generatedDir + materialName + "_PS.hlsl";
        mPS = Renderer::Instance->CreateShader(target, ShaderType::PixelShader);
    }
    else {

        std::string generatedDir(R"(Assets/Shaders/Generated/OpenGL/)");
        std::string target = generatedDir + materialName + "_VS.glsl";
        mVS = Renderer::Instance->CreateShader(target, ShaderType::VertexShader);
        target = generatedDir + materialName + "_PS.glsl";
        mPS = Renderer::Instance->CreateShader(target, ShaderType::PixelShader);
    }

    mPerMaterial = Renderer::Instance->CreateConstantBuffer(ConstantBufferDataType::PerMaterial, 1024);
    mDepthStencilState = Renderer::Instance->CreateDepthStencilState();
    BuildMaterialParamLayout();
}

float Material::GetFloat(const std::string &name) {

    auto pair = mFloatParams.find(name);
    if (pair == mFloatParams.end()) {
        return 0;
    }
    else {
        return pair->second;
    }
}

Vector4f Material::GetVector4(const std::string &name) {

    auto pair = mVector4Params.find(name);
    if (pair == mVector4Params.end()) {
        return {0, 0, 0, 0};
    }
    else {
        return pair->second;
    }
}

Matrix4x4f Material::GetMatrix(const std::string &name) {

    auto pair = mMatrixParams.find(name);
    if (pair == mMatrixParams.end()) {
        return {};
    }
    else {
        return pair->second;
    }
}

std::shared_ptr<Texture> Material::GetTexture(const std::string &name) {

    auto pair = mTextureParams.find(name);
    if (pair == mTextureParams.end()) {
        return nullptr;
    }
    else {
        return pair->second;
    }
}

int Material::GetParamOffset(const std::string &name) {

    auto pair = mParamDefines.find(name);
    if (pair == mParamDefines.end()) {
        return -1;
    }
    else {
        return pair->second.mOffset;
    }
}

MaterialParameterType Material::GetParamType(const std::string &name) {

    auto pair = mParamDefines.find(name);
    if (pair == mParamDefines.end()) {
        return MaterialParameterType::Unknown;
    }
    else {
        return pair->second.mMatType;
    }
}

void Material::SetFloat(const std::string &name, float value) {

    if (!CheckParamExist(name)) {
        return;
    }

    auto pair = mFloatParams.find(name);
    if (pair == mFloatParams.end()) {
        mFloatParams.insert({name, value});
    }
    else {
        pair->second = value;
    }

    auto offset = GetParamOffset(name);
    if (offset == -1) {
        Logger::Warning("%s not found in parameter defines", name.c_str());
    }
    else {
        char* buffer = (char*)mPerMaterial->GetData();
        char* address = buffer + offset;
        memcpy(address, &value, sizeof(float));
    }
}

void Material::SetVector4(const std::string &name, Vector4f value) {

    if (!CheckParamExist(name)) {
        return;
    }

    auto pair = mVector4Params.find(name);
    if (pair == mVector4Params.end()) {
        mVector4Params.insert({name, value});
    }
    else {
        pair->second = value;
    }

    auto offset = GetParamOffset(name);
    if (offset == -1) {
        Logger::Warning("%s not found in parameter defines", name.c_str());
    }
    else {
        char* buffer = (char*)mPerMaterial->GetData();
        char* address = buffer + offset;
        memcpy(address, &value, sizeof(Vector4f));
    }
}

void Material::SetMatrix(const std::string &name, Matrix4x4f value) {

    if (!CheckParamExist(name)) {
        return;
    }

    auto pair = mMatrixParams.find(name);
    if (pair == mMatrixParams.end()) {
        mMatrixParams.insert({name, value});
    }
    else {
        pair->second = value;
    }

    auto offset = GetParamOffset(name);
    if (offset == -1) {
        Logger::Warning("%s not found in parameter defines", name.c_str());
    }
    else {
        char* buffer = (char*)mPerMaterial->GetData();
        char* address = buffer + offset;
        memcpy(address, &value, sizeof(Matrix4x4f));
    }
}

void Material::SetTexture(const std::string &name, const std::shared_ptr<Texture> &value) {

    if (!CheckParamExist(name)) return;

    auto pair = mTextureParams.find(name);
    if (pair == mTextureParams.end()) {
        mTextureParams.insert({name, value});
    }
    else {
        pair->second = value;
    }
}

bool Material::CheckParamExist(const std::string &name) const {

    if (mParamDefines.find(name) == mParamDefines.end()) {
        return false;
    }
    return true;
}

void Material::BuildMaterialParamLayout() {

    mParamDefines["BaseColor"] = {MaterialParameterType::Vector4, 0, TextureShaderType::PS};
    mParamDefines["ModelMatrix"] = {MaterialParameterType::Matrix, 16, TextureShaderType::VS};

    mParamDefines["MainTex"] = {MaterialParameterType::Texture2D, 0, TextureShaderType::PS};
}


