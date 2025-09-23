#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <optional>

// Forward declaration
class VisualBlock;

struct BlockConnection
{
    int fromBlockId;
    std::string fromOutput;
    int toBlockId;
    std::string toInput;
};

class BlockGraph
{
public:
    // Add a block to the graph, returns its unique ID
    int addBlock(std::unique_ptr<VisualBlock> block);
    // Remove a block by ID
    void removeBlock(int blockId);
    // Get a block by ID
    VisualBlock *getBlock(int blockId);
    // Add a connection between blocks
    void addConnection(int fromBlockId, const std::string &fromOutput, int toBlockId, const std::string &toInput);
    // Remove a connection
    void removeConnection(int fromBlockId, const std::string &fromOutput, int toBlockId, const std::string &toInput);
    // Get all connections
    const std::vector<BlockConnection> &getConnections() const { return connections_; }
    // Get all blocks
    const std::unordered_map<int, std::unique_ptr<VisualBlock>> &getBlocks() const { return blocks_; }

private:
    int nextBlockId_ = 1;
    std::unordered_map<int, std::unique_ptr<VisualBlock>> blocks_;
    std::vector<BlockConnection> connections_;
};
