#include <spdlog/spdlog.h>

#pragma once
#include <imgui_node_editor.h>
#include <vector>
#include <memory>
#include "core/components/base/visual_block.hpp"

namespace ed = ax::NodeEditor;

namespace core
{
    class VisualWindow
    {
    public:
        VisualWindow()
            : editorContext(ed::CreateEditor()) {}

        ~VisualWindow()
        {
            ed::DestroyEditor(editorContext);
        }

        void addBlock(std::unique_ptr<VisualBlock> block)
        {
            spdlog::info("VisualWindow::addBlock called. Block count before: {}", blocks.size());
            blocks.push_back(std::move(block));
            spdlog::info("Block count after: {}", blocks.size());
        }

        void render()
        {
            spdlog::info("VisualWindow::render called. Block count: {}", blocks.size());
            ed::SetCurrentEditor(editorContext);
            ed::Begin("MainNodeEditor");
            for (auto &block : blocks)
            {
                block->render();
            }
            ed::End();
        }

        void clear()
        {
            spdlog::info("VisualWindow::clear called. Clearing {} blocks.", blocks.size());
            blocks.clear();
        }

    private:
        ed::EditorContext *editorContext;
        std::vector<std::unique_ptr<VisualBlock>> blocks;
    };

}