#pragma once

namespace SingularEngine
{
    class PanelBase
    {
    public:
        PanelBase() = default;
        virtual ~PanelBase() = default;

        virtual void Initialize() = 0;
        virtual void Finalize() = 0;
        virtual void Render() = 0;

    protected:
        bool mbShowing{};
    };
}