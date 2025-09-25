#pragma once
#include <memory>
#include <string>

class AppContext;

namespace ui::components
{

    class MainMenuBar final
    {
    public:
        explicit MainMenuBar(AppContext &ctx) : ctx(ctx) {}
        void render();

    private:
        AppContext &ctx;
        void renderFileMenu();
        void renderViewMenu();
        void renderSettingsMenu();
        void renderHelpMenu();
    };

} // namespace ui::components
