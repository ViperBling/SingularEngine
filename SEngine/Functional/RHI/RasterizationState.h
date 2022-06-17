#pragma once

namespace SingularEngine
{
    enum class RasterizationFillMode
    {
        Solid = 0,
        WireFrame,
    };

    enum class RasterizationCullMode
    {
        None = 0,
        Front = 1,
        Back = 2
    };

    struct RasterizationStateDesc
    {
        RasterizationFillMode fillMode;
        RasterizationCullMode cullMode;
        bool FrontCounterClockWise;
    };

    class RasterizationState
    {
    public:
        RasterizationState(const RasterizationStateDesc& config);
        virtual ~RasterizationState();

    protected:
        RasterizationStateDesc mDesc;
    };
}