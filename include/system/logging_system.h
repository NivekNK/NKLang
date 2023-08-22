#pragma once

#include <mutex>

/** @file */

/**
 * @defgroup LOG_ENABLED Log Enabled
 * @brief Defines to enable the logger API.
 * @{
 */

#if defined(NK_RELEASE)
    #define NK_LOG_TRACE_ENABLED 0
    #define NK_LOG_DEBUG_ENABLED 0
#else
    #define NK_LOG_TRACE_ENABLED 1
    #define NK_LOG_DEBUG_ENABLED 1
#endif

#define NK_LOG_INFO_ENABLED 1
#define NK_LOG_WARN_ENABLED 1

/** @} */

#if defined(NK_PLATFORM_WINDOWS)
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#include "system/file_system.h"

namespace nk {
    // class File;
    enum class LoggingPriority {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
    };

    enum class FontConsoleColor : i8 {
        None = -1,
        Black,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White,
    };

    enum class FontConsoleStyle : i8 {
        None = -1,
        Bold = 1,
        Underline = 4,
    };

    struct LogStyle {
        FontConsoleColor font = FontConsoleColor::White;
        FontConsoleColor background = FontConsoleColor::None;
        FontConsoleStyle style = FontConsoleStyle::None;
    };

    struct LoggingSystemInfo {
        LogStyle trace_style = LogStyle{};
        LogStyle debug_style = LogStyle{FontConsoleColor::Cyan};
        LogStyle info_style = LogStyle{FontConsoleColor::Green};
        LogStyle warn_style = LogStyle{
            FontConsoleColor::Yellow,
            FontConsoleColor::Black,
            FontConsoleStyle::Bold};
        LogStyle error_style = LogStyle{
            FontConsoleColor::Red,
            FontConsoleColor::Black,
            FontConsoleStyle::Bold};
        LogStyle fatal_style = LogStyle{
            FontConsoleColor::White,
            FontConsoleColor::Red,
            FontConsoleStyle::Bold};
    };

    class LoggingSystem {
    public:
        static void init(
            LoggingPriority priority = LoggingPriority::Info,
            const char* file_output_path = "logs/",
            const LoggingSystemInfo& create_info = LoggingSystemInfo{}
        );
        static bool is_initialized();
        static void set_priority(LoggingPriority priority);
        static void set_file_output(bool enabled);

        template<typename... Args>
        static void trace(std::string_view fmt, Args&&... args) {
            if (!get().initialized || get().priority > LoggingPriority::Trace)
                return;
            std::string message;
            std::vformat_to(
                std::back_inserter(message),
                fmt,
                std::make_format_args(std::forward<Args>(args)...)
            );
            log(message, "Trace", get().system_info.trace_style);
        }

        template<typename... Args>
        static void debug(std::string_view fmt, Args&&... args) {
            if (!get().initialized || get().priority > LoggingPriority::Debug)
                return;
            std::string message;
            std::vformat_to(
                std::back_inserter(message),
                fmt,
                std::make_format_args(std::forward<Args>(args)...)
            );
            log(message, "Debug", get().system_info.debug_style);
        }

        template<typename... Args>
        static void info(std::string_view fmt, Args&&... args) {
            if (!get().initialized || get().priority > LoggingPriority::Info)
                return;
            std::string message;
            std::vformat_to(
                std::back_inserter(message),
                fmt,
                std::make_format_args(std::forward<Args>(args)...)
            );
            log(message, "Info", get().system_info.info_style);
        }

        template<typename... Args>
        static void warning(std::string_view fmt, Args&&... args) {
            if (!get().initialized || get().priority > LoggingPriority::Warning)
                return;
            std::string message;
            std::vformat_to(
                std::back_inserter(message),
                fmt,
                std::make_format_args(std::forward<Args>(args)...)
            );
            log(message, "Warning", get().system_info.warn_style);
        }

        template<typename... Args>
        static void error(std::string_view fmt, Args&&... args) {
            if (!get().initialized || get().priority > LoggingPriority::Error)
                return;
            std::string message;
            std::vformat_to(
                std::back_inserter(message),
                fmt,
                std::make_format_args(std::forward<Args>(args)...)
            );
            log(message, "Error", get().system_info.error_style);
        }

        template<typename... Args>
        static void fatal(std::string_view fmt, Args&&... args) {
            if (!get().initialized || get().priority > LoggingPriority::Fatal)
                return;
            std::string message;
            std::vformat_to(
                std::back_inserter(message),
                fmt,
                std::make_format_args(std::forward<Args>(args)...)
            );
            log(message, "Fatal", get().system_info.fatal_style);
        }

    private:
        LoggingSystem() {}

        LoggingSystem(const LoggingSystem&) = delete;
        LoggingSystem& operator=(const LoggingSystem&) = delete;

        ~LoggingSystem() { this->initialized = false; }

        static LoggingSystem& get() {
            static LoggingSystem instance;
            return instance;
        }

#if defined(NK_PLATFORM_WINDOWS)
        static void activate_virtual_terminal();
#endif
        static const char* colorize(i8 font, i8 back = -1, i8 style = -1);
        static void
        log(std::string_view message,
            std::string_view logger_name,
            const LogStyle& log_style);

        bool initialized = false;
        LoggingPriority priority;
        LoggingSystemInfo system_info;

        std::mutex log_mutex;

        bool file_output_enabled;
        Scope<File> file;
    };
} // namespace nk

/**
 * @defgroup LOGS Logs
 * @brief Defines to send messages to the logger.
 * @{
 */
#if NK_LOG_TRACE_ENABLED == 1
    #define TraceLog(...) ::nk::LoggingSystem::trace(__VA_ARGS__)
#else
    #define TraceLog(...)
#endif

#if NK_LOG_DEBUG_ENABLED == 1
    #define DebugLog(...) ::nk::LoggingSystem::debug(__VA_ARGS__)
#else
    #define DebugLog(...)
#endif

#if NK_LOG_INFO_ENABLED == 1
    #define InfoLog(...) ::nk::LoggingSystem::info(__VA_ARGS__)
#else
    #define InfoLog(...)
#endif

#if NK_LOG_WARN_ENABLED == 1
    #define WarnLog(...) ::nk::LoggingSystem::warning(__VA_ARGS__)
#else
    #define WarnLog(...)
#endif

#define ErrorLog(...) ::nk::LoggingSystem::error(__VA_ARGS__)
#define FatalLog(...) ::nk::LoggingSystem::fatal(__VA_ARGS__)
/** @} */
