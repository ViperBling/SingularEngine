#pragma once

#include <memory>
#include <vector>

#include "Functional/GameObject/GameObject.h"
#include "Functional/GameObject/Components/CameraComponent/CameraComponent.h"
#include "Functional/GameObject/Components/LightComponent/LightComponent.h"
#include "Functional/RHI/ConstantBuffer.h"
#include "Functional/RHI/RenderItem.h"
#include "Functional/RHI/RenderTarget.h"
#include "Functional/RHI/RasterizationState.h"

namespace SingularEngine
{
    class SceneManager
    {
    public:
        SceneManager();

        void Initialize();
        void Finalize();
        void Tick();
        void Render(const std::shared_ptr<RenderTarget>& rt, const std::shared_ptr<RasterizationState>& rs);

        void LoadScene(const std::string& path);

        std::shared_ptr<GameObject> GetRoot();
        std::shared_ptr<GameObject> CreateGameObject(const std::string& name, const std::shared_ptr<GameObject>& parent);

        void RegisterCamera(CameraComponent* camera);
        void UnregisterCamera(CameraComponent* camera);
        CameraComponent* GetMainCamera();

        void RegisterLight(LightComponent* light);
        void UnregisterLight(LightComponent* light);

        std::shared_ptr<ConstantBuffer> GetConstantBufferPerScene();

    private:
        void TickGameObject(GameObject* obj);
        void UpdateConstantBufferPerScene();
        void UpdateCameraMatrix();
        void UpdateLightData();
        void UpdateShadowData();

    public:
        static SceneManager* Instance;

    private:
        std::shared_ptr<GameObject> mRoot = nullptr;
        std::vector<std::shared_ptr<GameObject>> mGameObjects;

        std::vector<CameraComponent*> mCameras;
        std::vector<LightComponent*> mLights;
        std::shared_ptr<ConstantBuffer> mConstantBufferPerScene = nullptr;
    };
}