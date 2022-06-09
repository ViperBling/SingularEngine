#include "GameObject.h"

using namespace SingularEngine;

GameObject::GameObject(const std::string &name) :
    mName(name),
    mTransformCompt(nullptr)
{
    mTransformCompt = new TransformComponent(this);
    mTransformCompt->Initialize();
}

GameObject::~GameObject() {

    mTransformCompt->Finalize();
    delete mTransformCompt;
    mTransformCompt = nullptr;
}
