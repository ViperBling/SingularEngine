#include <imgui.h>

#include "LogPanel.h"

using namespace SingularEngine;


void LogPanel::Initialize() {

}

void LogPanel::Render() {

    ImGui::Begin("Log Window", &mbShowing);
    ImGui::End();
}

void LogPanel::Finalize() {

}
