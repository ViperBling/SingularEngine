#pragma once

#include "Functional/Application/Windows/WindowsApplication.h"
#include "SEditorPanels/HierarchyPanel.h"
#include "SEditorPanels/LogPanel.h"
#include "SEditorPanels/GamePanel.h"
#include "SEditorPanels/InspectorPanel.h"

namespace SingularEngine
{
    class WindowsEditor : public WindowsApplication
    {
    public:
        WindowsEditor();
        void Initialize(std::shared_ptr<ApplicationInitParams> param) override;
        void Tick() override;
        void Render() override;
        void Finalize() override;

    protected:
        void OnWindowSizeChange(int width, int height) override;

    private:
        void RenderEditorBegin();
        void RenderEditorEnd();

    public:
        static WindowsEditor* Instance;
        HierarchyPanel mHierarchyPanel;
        LogPanel mLogPanel;
        GamePanel mGamePanel;
        InspectorPanel mInspectorPanel;
    };
}