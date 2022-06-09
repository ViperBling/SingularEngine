#include <memory>
#include <imgui.h>
#include <imgui_impl_opengl3.h>

#ifdef SINGULAR_PLATFORM_WINDOWS
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#endif

#include "GUIManager.h"

using namespace SingularEngine;

void GUIManager::Initialize(bool docking, bool mutivp) {

}

void GUIManager::Begin() {

}

void GUIManager::End() {

}

void GUIManager::Finalize() {

}

HRESULT GUIManager::HandleEvents(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    return 0;
}

void GUIManager::HandleMultiViewport(HWND hwnd, LPARAM lparam) {

}

void GUIManager::TestGUI() {

}
