#pragma once

#include "Functional/Application/Windows/WindowsApplication.h"

namespace SingularEngine
{
    class WindowsRuntime : public WindowsApplication
    {
    public:
        void Initialize(std::shared_ptr<ApplicationInitParams> param) override;
        void Render() override;
        void Tick() override;

    protected:
        void OnWindowSizeChange(int width, int height) override;
    };
}