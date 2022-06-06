#include "RenderTarget.h"

using namespace SingularEngine;

void RenderTarget::Resize(int width, int height) {

    mDesc.width = width;
    mDesc.height = height;
}
