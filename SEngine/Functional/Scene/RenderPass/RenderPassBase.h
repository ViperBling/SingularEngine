#pragma once

namespace SingularEngine
{
    class RenderPassBase
    {
    public:
        virtual void ResizeResolution(int width, int height) {}
    };
}