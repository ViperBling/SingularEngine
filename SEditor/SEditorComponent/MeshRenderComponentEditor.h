#pragma once

#include <memory>

#include "Functional/GameObject/Components/MeshRenderComponent/MeshRenderComponent.h"

namespace SingularEngine
{
    class MeshRenderComponentEditor
    {
    public:
        static void Render(const std::shared_ptr<MeshRenderComponent>& meshRender);
    };
}