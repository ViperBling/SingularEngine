#include <iostream>
#include "SRuntime/Windows/WindowsRuntime.h"

#include "Functional/RHI/Material.h"

using namespace SingularEngine;

int main()
{
    auto param = std::make_shared<ApplicationInitParams>();
    param->RenderAPIType = RenderAPI::D3D11;
    param->WindowWidth = 1920;
    param->WindowHeight = 1080;
    param->LogFile = (char*)"Player";
    param->LogDir = (char*)"Logs";
    param->EditorMode = false;

    auto app = new WindowsRuntime();
    app->Initialize(param);
    app->Run();
    app->Finalize();
    delete app;

    return 0;
}
