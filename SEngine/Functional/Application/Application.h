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
        virtual void Finalize() = 0;
        virtual void Run();
        virtual void Tick() = 0;
        virtual void Render() = 0;

        const std::shared_ptr<ApplicationInitParams>& GetConfig() const { return mConfig; }

    public:
        bool mbQuit;
        std::shared_ptr<ApplicationInitParams> mConfig;
    };
}