#pragma once

#include "PanelBase.h"

namespace SingularEngine
{
    class LogPanel : public PanelBase
    {
    public:
        void Initialize() override;
        void  Render() override;
        void Finalize() override;
    };
}