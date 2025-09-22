#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/dup_filter_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/cfg/env.h>
#include <chrono>
#include <memory>

namespace SpdlogDedupGlobal
{
    /**
     * @brief Set up the global spdlog logger with deduplication and console sinks
     *
     * This function configures spdlog to suppress repeated messages and format output without timestamps.
     */
    inline void setup_global_logger()
    {
        spdlog::cfg::load_env_levels();
        auto dedup_sink = std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(25)); // Suppress repeats for 25 seconds
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto logger = std::make_shared<spdlog::logger>("global_logger", spdlog::sinks_init_list{dedup_sink, console_sink});
        logger->set_pattern("[%l] %v"); // Only log level and message, no timestamp
        spdlog::set_default_logger(logger);
    }
}
