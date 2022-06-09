#include "SceneManager.h"
#include "Resource/AssetManager/AssetLoader.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/GameObject/Components/MeshRenderComponent/MeshRenderComponent.h"
#include "Functional/Scene/GizmoCreator.h"
#include "Functional/Scene/RenderPass/RenderPassManager.h"


using namespace SingularEngine;

SceneManager* SceneManager::Instance = nullptr;

SceneManager::SceneManager() :
    mCameras()
{

}

void SceneManager::Initialize() {

    mConstantBufferPerScene = Renderer::Instance->CreateConstantBuffer(ConstantBufferDataType::PerFrame, sizeof(ConstantBufferDataPerFrame));
    mRoot = std::make_shared<GameObject>("Root");
}

void SceneManager::Finalize() {

    mRoot.reset();
    mConstantBufferPerScene.reset();
}

void SceneManager::Tick() {

    TickGameObject(mRoot.get());
    UpdateConstantBufferPerScene();
}

void SceneManager::Render(const std::shared_ptr<RenderTarget> &rt, const std::shared_ptr<RasterizationState> &rs) {

    RenderPassManager::Instance->RenderShadowMap();
    RenderPassManager::Instance->RenderMeshMaterials(rs);
    RenderPassManager::Instance->RenderPostProcess(rt);
}

void SceneManager::LoadScene(const std::string &path) {

    auto camera = SceneManager::Instance->CreateGameObject("Camera", nullptr);
    camera->GetTransform()->SetPosition(10, 10, -45);
    camera->AddComponent<CameraComponent>();

    // TODO

    // ground
    auto ground = SceneManager::Instance->CreateGameObject("ground", nullptr);
    ground->GetTransform()->SetScale(1000, 1, 1000);
    ground->GetTransform()->SetPosition(0, 0, 0);
    auto groundMesh = GizmoCreator::CreatePlane();
    auto groundMeshComp = ground->AddComponent<MeshRenderComponent>();
    groundMeshComp->SetMesh(groundMesh);
    auto groundMaterial = Renderer::Instance->CreateMaterial("Color_Mesh", MaterialType::MeshRender);
    groundMaterial->SetVector4("BaseColor", Vector4f(0.4f, 0.4f, 0.4f, 1.0f));
    groundMeshComp->SetMaterial(0, groundMaterial);

    // cube
    auto cube = SceneManager::Instance->CreateGameObject("cube", nullptr);
    cube->GetTransform()->SetScale(2, 2, 2);
    cube->GetTransform()->SetPosition(0, 1, -10);
    auto cubeMesh = GizmoCreator::CreateCube();
    auto cubeMeshComp = cube->AddComponent<MeshRenderComponent>();
    cubeMeshComp->SetMesh(cubeMesh);
    auto cubeMaterial = Renderer::Instance->CreateMaterial("Color_Mesh", MaterialType::MeshRender);
    cubeMaterial->SetVector4("BaseColor", Vector4f(0.4f, 0.6f, 0.4f, 1.0f));
    cubeMeshComp->SetMaterial(0, cubeMaterial);

    auto light = SceneManager::Instance->CreateGameObject("Light", nullptr);
    light->GetTransform()->SetPosition(0, 35, 0);
    light->GetTransform()->SetEuler(-0.87, 1.8, 0);
    auto lightComp = light->AddComponent<LightComponent>();
    lightComp->SetColor(Color(0.8, 0.8, 0.8, 1));
    lightComp->SetIntensity(2);
}

std::shared_ptr<GameObject> SceneManager::GetRoot() {

    return mRoot;
}

std::shared_ptr<GameObject> SceneManager::CreateGameObject(
    const std::string &name,
    const std::shared_ptr<GameObject> &parent) {

    auto obj = std::make_shared<GameObject>(name);
    if (parent == nullptr) {
        obj->GetTransform()->SetParent(mRoot->GetTransform());
        mRoot->GetTransform()->AddChild(obj->GetTransform());
    }
    else {
        obj->GetTransform()->SetParent(parent->GetTransform());
        parent->GetTransform()->AddChild(obj->GetTransform());
    }
    mGameObjects.emplace_back(obj);

    return obj;
}

void SceneManager::RegisterCamera(CameraComponent *camera) {

    mCameras.emplace_back(camera);
}

void SceneManager::UnregisterCamera(CameraComponent *camera) {

    for (auto it = mCameras.begin(); it != mCameras.end(); it++) {
        auto element = *it;
        if (element == camera) {
            mCameras.erase(it);
            return;
        }
    }
}

CameraComponent *SceneManager::GetMainCamera() {

    if (mCameras.empty()) return nullptr;
    return mCameras.at(0);
}

void SceneManager::RegisterLight(LightComponent *light) {

    if (mLights.size() >= 5) {
        Logger::Warning("Light count must <= 5");
        return;
    }
    mLights.emplace_back(light);
}

void SceneManager::UnregisterLight(LightComponent *light) {

    for (auto it = mLights.begin(); it != mLights.end(); it++) {
        auto element = *it;
        if (element == light) {
            mLights.erase(it);
            return;
        }
    }
}

std::shared_ptr<ConstantBuffer> SceneManager::GetConstantBufferPerScene() {

    return mConstantBufferPerScene;
}

void SceneManager::TickGameObject(GameObject *obj) {

    obj->Tick();
    for (auto child : obj->GetTransform()->GetChildren()) {
        TickGameObject(child->GetOwner());
    }
}

void SceneManager::UpdateConstantBufferPerScene() {

    UpdateCameraMatrix();
    UpdateLightData();
    UpdateShadowData();
}

void SceneManager::UpdateCameraMatrix() {

    auto mainCamera = GetMainCamera();
    if (mainCamera == nullptr) {
        Logger::Error("No Camera in scene!");
        return;
    }

    auto data = (ConstantBufferDataPerFrame*)mConstantBufferPerScene->GetData();
    auto viewMatrix = mainCamera->GetViewMatrix();
    auto projectionMatrix = mainCamera->GetProjectionMatrix();
    data->mViewMatrix = viewMatrix;
    data->mProjectionMatrix = projectionMatrix;
    data->mVP = projectionMatrix * viewMatrix;
}

void SceneManager::UpdateLightData() {

    auto data = (ConstantBufferDataPerFrame*)mConstantBufferPerScene->GetData();
    int spotLightCount = 0;
    int pointLightCount = 0;
    for (auto light : mLights) {

        if (light->GetLightType() == LightType::Directional) {
            data->mDirectionLight.mColor = light->GetColor();
            data->mDirectionLight.mDirection = light->GetOwner()->GetTransform()->GetForward();
            data->mDirectionLight.mIntensity = light->GetIntensity();
        }
        else if (light->GetLightType() == LightType::Spot) {
            data->mSpotLight[spotLightCount].mPosition = light->GetOwner()->GetTransform()->GetPosition();
            data->mSpotLight[spotLightCount].mDirection = light->GetOwner()->GetTransform()->GetForward();
            data->mSpotLight[spotLightCount].mColor = light->GetColor();
            data->mSpotLight[spotLightCount].mIntensity = light->GetIntensity();
        }
        else if (light->GetLightType() == LightType::Point) {
            data->mPointLight[pointLightCount].mPosition = light->GetOwner()->GetTransform()->GetPosition();
            data->mPointLight[pointLightCount].mColor = light->GetColor();
            data->mPointLight[pointLightCount].mIntensity = light->GetIntensity();
        }
        else {
            SINGULAR_ASSERT(false);
        }
    }

    for (int i = spotLightCount; i < 4; i++)
    {
        data->mSpotLight[i].mIntensity.x = 0;
    }
    for (int i = pointLightCount; i < 4; i++)
    {
        data->mPointLight[i].mIntensity.x = 0;
    }
}

void SceneManager::UpdateShadowData() {

    auto data = (ConstantBufferDataPerFrame*)mConstantBufferPerScene->GetData();
    for (auto light : mLights) {
        if (light->GetLightType() == LightType::Directional) {
            data->mLightViewProj = light->GetLightViewProjMatrix();
        }
    }
}


