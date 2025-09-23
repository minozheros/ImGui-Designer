
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
            blocks.push_back(std::move(block));
        }

        void render()
        {
            ed::SetCurrentEditor(editorContext);
            ed::Begin("MainNodeEditor");
            for (auto &block : blocks)
            {
                block->render();
            }
            ed::End();
        }

        void clear() { blocks.clear(); }

    private:
        ed::EditorContext *editorContext;
        std::vector<std::unique_ptr<VisualBlock>> blocks;
    };

}