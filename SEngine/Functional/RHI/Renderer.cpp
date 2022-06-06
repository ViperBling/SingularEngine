#include <algorithm>

#include "Renderer.h"

using namespace SingularEngine;

Renderer* Renderer::Instance = nullptr;

Renderer::Renderer() :
    mContext(nullptr)
{
    mAPIType = RenderAPI::None;
}


std::shared_ptr<RenderContext> Renderer::GetContext() {

    return mContext;
}

RenderAPI Renderer::GetRenderAPI() const {

    return mAPIType;
}

void Renderer::CreateDefaultRasterizationState() {

    RasterizationStateDesc desc{};
    desc.cullMode = RasterizationCullMode::Back;
    desc.fillMode = RasterizationFillMode::Solid;
    desc.FrontCounterClockWise = false;
    mDefaultRasterizationState = CreateRasterizationState(desc);
}
