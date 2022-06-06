#pragma once

namespace SingularEngine
{
    enum class DEPTH_WRITE_MASK
    {
        DEPTH_WRITE_MASK_ZERO = 0,
        DEPTH_WRITE_MASK_ALL = 1,
    };

    enum class COMPARISON_FUNC
    {
        COMPARISON_NEVER = 1,
        COMPARISON_LESS = 2,
        COMPARISON_EQUAL = 3,
        COMPARISON_LESS_EQUAL = 4,
        COMPARISON_GREATER = 5,
        COMPARISON_NOT_EQUAL = 6,
        COMPARISON_GREATER_EQUAL = 7,
        COMPARISON_ALWAYS = 8,
    };

    class DepthStencilState
    {
    public:
        DepthStencilState();
        virtual ~DepthStencilState() = default;

        bool GetDepthEnable() const { return mbDepthEnable; }
        bool GetStencilEnable() const { return mbStencilEnable; }
        DEPTH_WRITE_MASK GetWriteMask() const { return mDepthWriteMask; }
        COMPARISON_FUNC GetDepthComparison() const { return mDepthComparisonFunc; }
        unsigned char GetStencilReadMask() const { return mStencilReadMask; }
        unsigned char GetStencilWriteMask() const { return mStencilWriteMask; }

        void SetDepthEnable(bool enable);
        void SetStencilEnable(bool enable);
        void SetWriteMask(DEPTH_WRITE_MASK mask);
        void SetDepthComparison(COMPARISON_FUNC func);
        void SetStencilReadMask(unsigned char mask);
        void SetStencilWriteMask(unsigned char mask);

        virtual void Bind() = 0;

    protected:
        bool mbDirty;
        bool mbDepthEnable;
        DEPTH_WRITE_MASK mDepthWriteMask;
        COMPARISON_FUNC mDepthComparisonFunc;
        bool mbStencilEnable;
        unsigned char mStencilReadMask;
        unsigned char mStencilWriteMask;
    };
}