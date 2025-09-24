#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include "app/helpers/app_context.hpp"
namespace core
{
    int WindowDestruction(ImGuiContext *&ctx, GLFWwindow *&window)
    {
        ImGui::SetCurrentContext(ctx);
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
        window = nullptr;
        ctx = nullptr;

        return 0;
    }
}