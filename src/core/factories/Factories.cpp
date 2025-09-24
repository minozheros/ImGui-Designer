#include "core/factories/factories.hpp"
#include "app/helpers/app_context.hpp"

namespace core
{

    Factories::Factories(AppContext *ctx) : ctx(ctx)
    {
        nodeFactory = std::make_unique<NodeFactory>();
    }

    void Factories::createAll()
    {
        spdlog::info("Factories: Starting creation of all factories");
        // Add more as needed
    }
}