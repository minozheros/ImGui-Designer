#include "node/graph/BlockGraph.hpp"
#include "core/components/base/VisualBlock.hpp"
#include <algorithm>

int BlockGraph::addBlock(std::unique_ptr<VisualBlock> block)
{
    int id = nextBlockId_++;
    blocks_[id] = std::move(block);
    return id;
}

void BlockGraph::removeBlock(int blockId)
{
    blocks_.erase(blockId);
    // Remove all connections to/from this block
    connections_.erase(std::remove_if(connections_.begin(), connections_.end(),
                                      [blockId](const BlockConnection &c)
                                      {
                                          return c.fromBlockId == blockId || c.toBlockId == blockId;
                                      }),
                       connections_.end());
}

VisualBlock *BlockGraph::getBlock(int blockId)
{
    auto it = blocks_.find(blockId);
    if (it != blocks_.end())
        return it->second.get();
    return nullptr;
}

void BlockGraph::addConnection(int fromBlockId, const std::string &fromOutput, int toBlockId, const std::string &toInput)
{
    connections_.push_back({fromBlockId, fromOutput, toBlockId, toInput});
}

void BlockGraph::removeConnection(int fromBlockId, const std::string &fromOutput, int toBlockId, const std::string &toInput)
{
    connections_.erase(std::remove_if(connections_.begin(), connections_.end(),
                                      [&](const BlockConnection &c)
                                      {
                                          return c.fromBlockId == fromBlockId && c.fromOutput == fromOutput &&
                                                 c.toBlockId == toBlockId && c.toInput == toInput;
                                      }),
                       connections_.end());
}
