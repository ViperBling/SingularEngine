#pragma once

#include "PanelBase.h"
#include "Functional/GameObject/GameObject.h"
#include "SEditorComponent/TransformComponentEditor.h"
#include "SEditorComponent/CameraComponentEditor.h"
#include "SEditorComponent/MeshRenderComponentEditor.h"
#include "SEditorComponent/LightComponentEditor.h"

namespace SingularEngine
{
    class InspectorPanel : public PanelBase
    {
    public:

        void Initialize() override;
        void Finalize() override;
        void Render() override;

        void OnSelectNewGameObject(GameObject* target);

    private:
        GameObject* mInspectingGameObject = nullptr;
        TransformComponent* mTransformComponent = nullptr;
        std::shared_ptr<CameraComponent> mCameraComponent = nullptr;
        std::shared_ptr<MeshRenderComponent> mMeshRenderComponent = nullptr;
        std::shared_ptr<LightComponent> mLightRenderComponent = nullptr;
    };
}