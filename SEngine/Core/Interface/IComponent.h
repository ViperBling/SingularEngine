#pragma once

namespace SingularEngine
{
    class IComponent
    {
    public:
        virtual void Initialize() = 0;
        virtual void Finalize() = 0;
        virtual void Tick() = 0;
    };
}