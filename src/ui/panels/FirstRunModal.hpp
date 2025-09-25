#pragma once
#include <memory>
#include <string>

namespace ui::panels
{

    class FirstRunModal final
    {
    public:
        // Request the modal to open (one-shot). Safe to call multiple times; only first matters until dismissed.
        void open();
        // Render should be called every frame; it will early-out if inactive.
        void render();
        bool isOpen() const { return open_ && !dismissed_; }
        bool isDismissed() const { return dismissed_; }
        bool shouldFocusPackManager() const { return requestFocusPackManager_; }
        void clearFocusRequest() { requestFocusPackManager_ = false; }

    private:
        bool open_ = false;          // Currently attempting to show popup
        bool triedInstall_ = false;  // Whether install attempt happened
        bool dismissed_ = false;     // User chose Skip / Close (prevents re-open this session)
        bool installing_ = false;    // Installation in progress (future async hook)
        bool installSucceeded_ = false; // Installation success flag
        std::string lastMessage_;    // Last status or error message
        bool requestFocusPackManager_ = false; // Set when we want the left dock to focus Pack Manager after closing
    };

} // namespace ui::panels
