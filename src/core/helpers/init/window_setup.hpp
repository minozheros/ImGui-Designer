#pragma once
#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <string>
namespace core
{

    inline GLFWwindow *setup_glfw_window_and_opengl_context(int width, int height, const std::string &title)
    {
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW");

        // Set OpenGL version (e.g., 3.3 Core)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        // Move window to second monitor if available
        int monitor_count = 0;
        GLFWmonitor **monitors = glfwGetMonitors(&monitor_count);
        if (monitor_count > 1 && monitors)
        {
            int xpos = 0, ypos = 0;
            glfwGetMonitorPos(monitors[1], &xpos, &ypos);
            glfwSetWindowPos(window, xpos, ypos);
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        return window;
    }
}