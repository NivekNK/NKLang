#include "nkpch.h"

#include "system/logging_system.h"

namespace nk {
    void LoggingSystem::init(
        LoggingPriority priority,
        const char* file_output_path,
        const LoggingSystemInfo& info
    ) {
        if (get().initialized) {
            return;
        }

        get().priority = priority;

        if (file_output_path != NULL) {
            get().file_output_enabled = true;
            std::string path = file_output_path;

            auto now = std::chrono::system_clock::now();
            auto time_t_now = std::chrono::system_clock::to_time_t(now);
            std::tm time_info;
            localtime_s(&time_info, &time_t_now);

            path += std::format("{}-{}-{}-log.txt", 1900 + time_info.tm_year, time_info.tm_mon + 1, time_info.tm_mday);
            get().file = File::open_scope(path, FileMode::Write);
        }
        get().system_info = info;
        get().initialized = true;
    }

    bool LoggingSystem::is_initialized() { return get().initialized; }

    void LoggingSystem::set_priority(LoggingPriority priority) {
        get().priority = priority;
    }

    void LoggingSystem::set_file_output(bool enabled) {
        get().file_output_enabled = enabled;
    }

#if defined(NK_PLATFORM_WINDOWS)
    void LoggingSystem::activate_virtual_terminal() {
        HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD consoleMode;
        GetConsoleMode(handleOut, &consoleMode);
        consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(handleOut, consoleMode);
    }
#endif

    const char* LoggingSystem::colorize(i8 font, i8 back, i8 style) {
        static char code[20];

        if (font >= 0)
            font += 30;
        else
            font = 0;
        if (back >= 0)
            back += 40;
        else
            back = 0;

        if (back > 0 && style > 0) {
            sprintf(code, "\033[%d;%d;%dm", font, back, style);
        } else if (back > 0) {
            sprintf(code, "\033[%d;%dm", font, back);
        } else {
            sprintf(code, "\033[%dm", font);
        }

        return code;
    }

    void LoggingSystem::log(
        std::string_view message,
        std::string_view logger_name,
        const LogStyle& log_style
    ) {
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        std::tm time_info;
        localtime_s(&time_info, &time_t_now);

        std::string formated_message = std::format(
            "[{:02}:{:02}:{:02}] {}: {}",
            time_info.tm_hour,
            time_info.tm_min,
            time_info.tm_sec,
            logger_name,
            message
        );

        std::scoped_lock lock(get().log_mutex);
        std::cout << colorize(
                         static_cast<i8>(log_style.font),
                         static_cast<i8>(log_style.background),
                         static_cast<i8>(log_style.style)
                     )
                  << formated_message << "\033[0m\n"
                  << std::flush;

        if (get().file_output_enabled && get().file) {
            get().file->write_line(formated_message);
        }
    }

} // namespace nk
