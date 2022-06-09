#include "SceneManager.h"
#include "Resource/AssetManager/AssetLoader.h"
#include "Functional/RHI/Renderer.h"
#include "Functional/GameObject/Components/MeshRenderComponent/MeshRenderComponent.h"


using namespace SingularEngine;

SceneManager* SceneManager::Instance = nullptr;

SceneManager::SceneManager() {

}

void SceneManager::Initialize() {

}

void SceneManager::Finalize() {

}

void SceneManager::Tick() {

}

void SceneManager::Render(const std::shared_ptr<RenderTarget> &rt, const std::shared_ptr<RasterizationState> &rs) {

}

void SceneManager::LoadScene(const std::string &path) {

}

std::shared_ptr<GameObject> SceneManager::GetRoot() {
    return std::shared_ptr<GameObject>();
}

std::shared_ptr<GameObject>
SceneManager::CreateGameObject(const std::string &name, const std::shared_ptr<GameObject> &parent) {
    return std::shared_ptr<GameObject>();
}

void SceneManager::RegisterCamera(CameraComponent *camera) {

}

void SceneManager::UnregisterCamera(CameraComponent *camera) {

}

CameraComponent *SceneManager::GetMainCamera() {
    return nullptr;
}

void SceneManager::RegisterLight(LightComponent *light) {

}

void SceneManager::UnregisterLight(LightComponent *light) {

}

std::shared_ptr<ConstantBuffer> SceneManager::GetConstantBufferPerScene() {
    return std::shared_ptr<ConstantBuffer>();
}

void SceneManager::TickGameObject(GameObject *obj) {

}

void SceneManager::UpdateConstantBufferPerScene() {

}

void SceneManager::UpdateCameraMatrix() {

}

void SceneManager::UpdateLightData() {

}

void SceneManager::UpdateShadowData() {

}


