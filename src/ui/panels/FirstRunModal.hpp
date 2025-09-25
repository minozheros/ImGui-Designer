#pragma once
#include <memory>
#include <string>

namespace ui::panels
{

    class FirstRunModal final
    {
    public:
        void open();
        void render();
        bool isOpen() const { return open_; }

    private:
        bool open_ = false;
        bool triedInstall_ = false;
        std::string lastMessage_;
    };

} // namespace ui::panels
