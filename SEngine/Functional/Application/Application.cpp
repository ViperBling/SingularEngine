#include "Application.h"
#include "Resource/AssetManager/AssetLoader.h"
#include "Core/Logging/Logger.h"

using namespace SingularEngine;

Application::Application() :
    mbQuit(false)
{

}

Application::~Application() {

    AssetLoader::Finalize();
}

void Application::Initialize(std::shared_ptr<ApplicationInitParams> params) {

    mConfig = params;
    Logger::InitLogger(params->LogDir.c_str(), params->LogFile.c_str());
    AssetLoader::Init();
}

void Application::Run() {

    while (true) {
        Tick();
        if (mbQuit) break;

        Render();
    }
}
