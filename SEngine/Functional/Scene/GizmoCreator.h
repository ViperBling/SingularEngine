#pragma once

#include <memory>
#include <array>

#include "Functional/RHI/Mesh.h"

namespace SingularEngine
{
    class GizmoCreator
    {
    public:
        static std::shared_ptr<Mesh> CreatePlane();
        static std::shared_ptr<Mesh> CreateCube();
    };
}