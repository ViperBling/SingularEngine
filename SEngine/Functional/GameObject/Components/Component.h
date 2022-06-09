#pragma once

#include <memory>

#include "Core/Interface/IComponent.h"

namespace SingularEngine
{

    class GameObject;

    class Component : public IComponent
    {
    public:
        explicit Component(GameObject* owner) : mOwner(owner) {}

        virtual ~Component() = default;

        GameObject* GetOwner() { return mOwner; }

    protected:
        GameObject* mOwner;
    };
}