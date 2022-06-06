#include "RenderItem.h"

using namespace SingularEngine;

void RenderItem::AllocateMaterials(int count) {

    mMaterials.clear();
    for (int i = 0; i < count; ++i) {
        mMaterials.emplace_back(nullptr);
    }
}

std::shared_ptr<Material> RenderItem::GetMaterial(int index) const {

    if (index >= mMaterials.size()) {
        return nullptr;
    }
    return mMaterials[index];
}

void RenderItem::SetMaterial(int index, const std::shared_ptr<Material> &material) {

    if (index >= mMaterials.size()) {
        return;
    }
    else {
        mMaterials[index] = material;
    }
}

size_t RenderItem::GetMaterialCount() const {

    return mMaterials.size();
}
