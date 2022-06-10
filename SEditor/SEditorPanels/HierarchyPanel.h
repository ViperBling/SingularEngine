#pragma once

#include <memory>

#include "PanelBase.h"
#include "Functional/Scene/SceneManager.h"

namespace SingularEngine
{
    class HierarchyPanel : public PanelBase
    {
    public:
        void Initialize() override;
        void Finalize() override;
        void Render() override;

    private:
        void RenderGameObject(GameObject* obj);

    private:
        GameObject* mSelectedObject = nullptr;
    };
}