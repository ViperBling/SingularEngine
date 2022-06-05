#pragma once

#include <memory>
#include <string>

#include "Platform/Platform.h"

namespace SingularEngine
{
    struct ApplicationInitParams
    {
        bool EditorMode;
        int WindowWidth;
        int WindowHeight;
        RenderAPI RenderAPIType;
        std::string LogDir;
        std::string LogFile;
    };

    class Application
    {
    public:
        Application();
        virtual ~Application();

    public:
        virtual void Initialize(std::shared_ptr<ApplicationInitParams> params);
        virtual void Finalize() noexcept = 0;
        virtual void Run() noexcept;
        virtual void Tick() noexcept = 0;
        virtual void Render() noexcept = 0;

        const std::shared_ptr<ApplicationInitParams>& GetConfig() const { return mConfig; }

    private:
        bool mbQuit;
        std::shared_ptr<ApplicationInitParams> mConfig;
    };
}