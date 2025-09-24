
#pragma once
#include <string>
#include <vector>
#include <core/types/base/ParameterBase.hpp>

namespace core
{
    class GenericNode
    {
        std::string title_;
        std::vector<IParameterBase *> params_;
        float prevNodeWidth_ = 0.0f;

    public:
        GenericNode(const std::string &title, const std::vector<IParameterBase *> &params);
        void render();
    };
}