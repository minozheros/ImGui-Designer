// main_factory.hpp
#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
struct AppContext;
#include <memory>
#include <spdlog/spdlog.h>
#include <entt/entt.hpp>
#include <imgui.h>
#include "core/factories/node_factory.hpp"

namespace core
{
    // MainFactory that aggregates sub-factories and coordinates creation
    class Factories
    {
    public:
        explicit Factories(AppContext *ctx);

        // High-level creation method
        void createAll();

        std::unique_ptr<NodeFactory> nodeFactory;

    private:
        AppContext *ctx;
    };
}