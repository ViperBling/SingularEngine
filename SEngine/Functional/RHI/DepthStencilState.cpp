#include "DepthStencilState.h"

using namespace SingularEngine;

DepthStencilState::DepthStencilState() :
    mbDirty(true),
    mbDepthEnable(true),
    mDepthWriteMask(DEPTH_WRITE_MASK::DEPTH_WRITE_MASK_ALL),
    mDepthComparisonFunc(COMPARISON_FUNC::COMPARISON_LESS),
    mbStencilEnable(false),
    mStencilReadMask(0xff),
    mStencilWriteMask(0xff)
{

}


void DepthStencilState::SetDepthEnable(bool enable) {

    mbDepthEnable = enable;
    mbDirty = true;
}

void DepthStencilState::SetStencilEnable(bool enable) {

    mbStencilEnable = enable;
    mbDirty = true;
}

void DepthStencilState::SetWriteMask(DEPTH_WRITE_MASK mask) {

    mDepthWriteMask = mask;
    mbDirty = true;
}

void DepthStencilState::SetDepthComparison(COMPARISON_FUNC func) {

    mDepthComparisonFunc = func;
    mbDirty = true;
}

void DepthStencilState::SetStencilReadMask(unsigned char mask) {

    mStencilReadMask = mask;
    mbDirty = true;
}

void DepthStencilState::SetStencilWriteMask(unsigned char mask) {

    mStencilWriteMask = mask;
    mbDirty = true;
}
