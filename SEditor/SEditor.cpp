#include <memory>

#include "SEditorWindows/WindowsEditor.h"

using namespace SingularEngine;

int main()
{
    auto param = std::make_shared<ApplicationInitParams>();
    param->RenderAPIType = RenderAPI::D3D11;
    param->WindowWidth = 1920;
    param->WindowHeight = 1080;
    param->LogFile = (char*)"Editor";
    param->LogDir = (char*)"Logs";
    param->EditorMode = true;

    auto app = new WindowsEditor();
    app->Initialize(param);
    app->Run();
    app->Finalize();
    delete app;

    return 0;
}