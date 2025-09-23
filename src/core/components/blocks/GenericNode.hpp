
#pragma once
#include <string>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
    class GenericNode
    {
        std::string title_;
        std::vector<core::IParameterBase *> params_;
        float prevNodeWidth_ = 0.0f;

    public:
        GenericNode(const std::string &title, const std::vector<core::IParameterBase *> &params);
        void render();
    };
}