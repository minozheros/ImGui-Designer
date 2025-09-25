#pragma once
#include <imgui.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#ifdef __linux__
namespace X11MouseFix
{
    /**
     * X11 multi-monitor coordinate fix: Only override invalid ImGui coordinates when mouse is actually in window
     *
     * This fixes an issue on X11 systems where ImGui reports invalid mouse coordinates (-10000, -10000)
     * in multi-monitor setups, particularly when the window is unfocused. We only correct the coordinates
     * when the mouse is actually within the window bounds to avoid interfering with normal operation.
     *
     * @param window The GLFW window to check mouse coordinates for
     */
    inline void applyMultiMonitorFix(GLFWwindow *window)
    {
        if (!window)
            return;

        ImGuiIO &io = ImGui::GetIO();

        // Check if ImGui has invalid mouse coordinates (common in X11 multi-monitor unfocused windows)
        bool imgui_has_invalid_coords = (io.MousePos.x < -10000.0f || io.MousePos.y < -10000.0f);

        if (imgui_has_invalid_coords)
        {
            // Get current mouse position (global screen coordinates)
            double global_x = 0.0, global_y = 0.0;
            glfwGetCursorPos(window, &global_x, &global_y);

            // Get window position and size
            int win_x = 0, win_y = 0, win_w = 0, win_h = 0;
            glfwGetWindowPos(window, &win_x, &win_y);
            glfwGetWindowSize(window, &win_w, &win_h);

            // Calculate relative coordinates
            double relative_x = global_x - win_x;
            double relative_y = global_y - win_y;

            // Check if mouse is actually within window bounds
            bool mouse_in_window = (relative_x >= 0 && relative_x < win_w &&
                                    relative_y >= 0 && relative_y < win_h);

            int glfw_focused = glfwGetWindowAttrib(window, GLFW_FOCUSED);
            int glfw_hovered = glfwGetWindowAttrib(window, GLFW_HOVERED);

            if (mouse_in_window)
            {
                // Only override coordinates if mouse is actually in window bounds
                io.MousePos = ImVec2((float)relative_x, (float)relative_y);
                // Demoted from info to debug (can trigger repeatedly while invalid coords persist)
                spdlog::debug("X11 multi-monitor fix: Corrected invalid coords - Global=({:.0f},{:.0f}) Window=({},{}) Relative=({:.0f},{:.0f}) -> ImGui=({:.1f},{:.1f}) GLFW(hovered={},focused={})",
                              global_x, global_y, win_x, win_y, relative_x, relative_y, io.MousePos.x, io.MousePos.y, glfw_hovered, glfw_focused);
            }
            else
            {
                spdlog::debug("X11 multi-monitor: Keeping invalid coords - mouse outside window bounds");
            }
        }
    }
}
#else
// Stub implementation for non-Linux platforms
namespace X11MouseFix
{
    inline void applyMultiMonitorFix(GLFWwindow * /*window*/)
    {
        // No-op on non-Linux platforms
    }
}
#endif