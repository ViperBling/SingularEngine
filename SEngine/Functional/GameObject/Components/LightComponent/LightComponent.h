#pragma once

#include "Core/Math/MathPCH.h"
#include "Functional/GameObject/Components/Component.h"

namespace SingularEngine
{
    enum class LightType
    {
        Directional,
        Spot,
        Point,
    };

    class LightComponent : public Component
    {
    public:
        LightComponent() = delete;
        explicit LightComponent(GameObject* owner) :
            Component(owner),
            mLightColor(1, 1, 1, 1),
            mIntensity(1.0f),
            mLightType(LightType::Directional)
        {}

        ~LightComponent() override = default;

        void Initialize() override;
        void Finalize() override;
        void Tick() override;

        Color& GetColor() { return mLightColor; }
        float& GetIntensity() {return mIntensity; }
        LightType GetLightType() const {return mLightType; }

        void SetColor(const Color& color) { mLightColor = color; }
        void SetIntensity(float intensity) { mIntensity = intensity; }
        void SetLightType(LightType lt);

        Matrix4x4f GetLightViewProjMatrix();

    private:
        Color mLightColor;
        float mIntensity;
        LightType mLightType;
    };
}