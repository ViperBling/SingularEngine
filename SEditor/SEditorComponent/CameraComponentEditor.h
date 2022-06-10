#pragma once

#include <memory>

#include "Functional/GameObject/Components/CameraComponent/CameraComponent.h"

namespace SingularEngine
{
    class CameraComponentEditor
    {
    public:
        static void Render(const std::shared_ptr<CameraComponent>& camera);
    };
}