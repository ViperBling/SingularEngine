#pragma once

#include <memory>
#include <string>
#include <map>
#include <typeindex>

#include "Functional/GameObject/Components/TransformComponent/TransformComponent.h"

namespace SingularEngine
{
    class GameObject
    {
    public:
        GameObject() = delete;
        explicit GameObject(const std::string& name);
        ~GameObject();


        template<typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
        std::shared_ptr<T> AddComponent() {

            auto compt = std::make_shared<T>(this);
            compt->Initialize();

            auto base = std::dynamic_pointer_cast<Component>(compt);
            auto pair = std::make_pair(std::type_index(typeid(T)), base);
            mComponents.insert(pair);

            return compt;
        }

        template<typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
        std::shared_ptr<T> GetComponent() {

            auto it = mComponents.find(std::type_index(typeid(T)));
            if (it == mComponents.end()) return nullptr;

            return std::dynamic_pointer_cast<T>(it->second);
        }

        template<typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
        void RemoveComponent() {

            auto it = mComponents.find(std::type_index(typeid(T)));
            if (it == mComponents.end())
            {
                return;
            }
            auto compt = std::dynamic_pointer_cast<T>(it->second);
            compt->Finalize();

            mComponents.erase(std::type_index(typeid(T)));
        }

        void Tick() {

            mTransformCompt->Tick();
            for (auto compt : mComponents) {
                compt.second->Tick();
            }
        }

    public:
        std::string GetName() { return mName; }
        void SetName(const std::string& name) { mName = name; }

        TransformComponent* GetTransform() { return mTransformCompt; }

    private:
        std::string mName;
        TransformComponent* mTransformCompt;
        std::multimap<std::type_index, std::shared_ptr<Component>> mComponents;
    };
}