#include "node/factories/Factories.hpp"
#include "app/context/AppContext.hpp"

Factories::Factories(AppContext *ctx) : ctx(ctx)
{
    nodeFactory = std::make_unique<NodeFactory>();
}

void Factories::createAll()
{
    spdlog::info("Factories: Starting creation of all factories");
    // Add more as needed
}