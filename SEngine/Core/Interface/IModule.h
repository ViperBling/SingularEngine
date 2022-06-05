#pragma once

namespace SingularEngine
{
    class IModule
    {
    public:
        virtual void Initialize() noexcept = 0;
        virtual void Finalize() noexcept = 0;
    };

    class ITickableModule : IModule
    {
    public:
        virtual void Tick() noexcept = 0;
    };
}