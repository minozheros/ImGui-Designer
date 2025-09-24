#pragma once
#include <spdlog/spdlog.h>
#include <atomic>

namespace core
{

    // Global running flag (should be defined in main.cpp)
    extern std::atomic<bool> running;

    // Signal handler for SIGINT
    inline void signalHandler(int signum)
    {
        running = false;
    }

    // Example event struct
    template <typename T = void>
    struct QuitEvent
    {
        // You can add data members here if needed
    };

    // Example event handler
    inline void on_quit(const QuitEvent<> &)
    {
        spdlog::info("QuitEvent received! Application will exit.");
    }

} // namespace core