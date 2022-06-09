#pragma once

#include <memory>

#include "Functional/RHI/RenderItem.h"
#include "Functional/RHI/D3D11/MeshD3D11.h"
#include "Functional/RHI/D3D11/ConstantBufferD3D11.h"
#include "Functional/RHI/D3D11/RenderContextD3D11.h"

namespace SingularEngine
{
    class RenderItemD3D11 : public RenderItem
    {
    public:
        RenderItemD3D11(
            const std::shared_ptr<Mesh>& mesh,
            const std::vector<std::shared_ptr<Material>>& materials,
            const std::shared_ptr<ConstantBuffer>& perObjects) :
            RenderItem(mesh, materials, perObjects)
        {}

        RenderItemD3D11(
            const std::shared_ptr<Mesh>& mesh,
            const std::shared_ptr<ConstantBuffer>& perObjects) :
            RenderItem(mesh, perObjects)
        {}

        ~RenderItemD3D11() override = default;

        void Render() const override;
        void Render(const std::shared_ptr<Material>& overrideMat) const override;

        static std::shared_ptr<RenderItemD3D11> Create(
            const std::shared_ptr<Mesh>& mesh,
            const std::vector<std::shared_ptr<Material>>& materials,
            const std::shared_ptr<ConstantBuffer>& perObject);

        static std::shared_ptr<RenderItemD3D11> Create(
            const std::shared_ptr<Mesh>& mesh,
            const std::shared_ptr<ConstantBuffer>& perObject);

    private:
        void BindConstantBufferPerObject(RenderContextD3D11* context) const;
        void DrawMesh(RenderContextD3D11* context, const std::shared_ptr<Material>& overrideMaterial) const;
    };
}