#include "core/components/visual_window.hpp"
#include "core/components/base/visual_block.hpp"
#include <imgui.h>
#include <memory>

// Example usage in your render loop:
//
// VisualWindow window;
// window.addBlock(std::make_unique<ImGuiWindowBlock>("My Window"));
// window.render();
//
// You can set position/size on ImGuiWindowBlock as needed.
