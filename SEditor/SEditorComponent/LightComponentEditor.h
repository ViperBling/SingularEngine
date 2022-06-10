#pragma once

#include <memory>

#include "Functional/GameObject/Components/LightComponent/LightComponent.h"

namespace SingularEngine
{
    class LightComponentEditor
    {
    public:
        static void Render(const std::shared_ptr<LightComponent>& light);
    };
}