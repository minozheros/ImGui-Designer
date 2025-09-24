#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>
#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>
#include "app/context/AppContext.hpp"

int WindowDestruction(ImGuiContext *&ctx, SDL_Window *window, SDL_GLContext glContext)
{
    ImGui::SetCurrentContext(ctx);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    ctx = nullptr;

    return 0;
}