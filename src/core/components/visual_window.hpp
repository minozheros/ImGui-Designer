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
            // Assign node id to block (if provided by the block) and set a sensible default position
            ed::EditorContext *ctx = editorContext;
            blocks.push_back(std::move(block));
            auto &added = blocks.back();
            try
            {
                ed::NodeId id = added->getNodeId();
                if (id.Get() == 0)
                {
                    // NodeId not set on the block; nothing to position
                    spdlog::debug("VisualWindow::addBlock: block has no NodeId to position");
                }
                else
                {
                    // Place new nodes near the center, staggered by count
                    ImVec2 center;
                    if (ImGui::GetMainViewport())
                    {
                        ImGuiViewport *vp = ImGui::GetMainViewport();
                        center = ImVec2(vp->Pos.x + vp->Size.x * 0.5f, vp->Pos.y + vp->Size.y * 0.5f);
                    }
                    else
                    {
                        center = ImVec2(640.0f, 360.0f);
                    }
                    ImVec2 offset = ImVec2(static_cast<float>(blocks.size() % 5) * 120.0f, static_cast<float>(blocks.size() / 5) * 60.0f);
                    ImVec2 pos = ImVec2(center.x - 100.0f + offset.x, center.y - 30.0f + offset.y);
                    ed::SetCurrentEditor(ctx);
                    ed::SetNodePosition(id, pos);
                    spdlog::info("VisualWindow::addBlock: positioned node {} at ({},{})", id.Get(), pos.x, pos.y);
                }
            }
            catch (...)
            {
                spdlog::warn("VisualWindow::addBlock: exception while positioning node");
            }
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