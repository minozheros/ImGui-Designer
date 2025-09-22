#pragma once
#include "core/components/blocks/params/block_params.hpp"
#include "core/components/base/visual_block.hpp"
#include <memory>

class ParametricVisualBlock : public VisualBlock
{
public:
    ParametricVisualBlock(std::unique_ptr<BlockParams> params)
        : params_(std::move(params)) {}
    BlockParams *getParams() { return params_.get(); }
    void setParams(std::unique_ptr<BlockParams> newParams) { params_ = std::move(newParams); }

protected:
    std::unique_ptr<BlockParams> params_;
};
