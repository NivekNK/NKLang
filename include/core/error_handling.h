#pragma once

namespace nk {
    inline static void info_report(
        std::string_view message,
        const u32 row,
        const u32 column,
        std::string_view file,
        std::string_view line
    ) {
        u32 digits = 0;
        for (u32 number = row; number > 0; number /= 10)
            digits++;

        LoggingSystem::info(
            "({}) {}.\n\n    {} | {}\n{:>{}}\n",
            file,
            message,
            row,
            line,
            "^--Here",
            14 + digits + column
        );
    }

    inline static void warning_report(
        std::string_view message,
        const u32 row,
        const u32 column,
        std::string_view file,
        std::string_view line
    ) {
        u32 digits = 0;
        for (u32 number = row; number > 0; number /= 10)
            digits++;

        LoggingSystem::warning(
            "({}) {}.\n\n    {} | {}\n{:>{}}\n",
            file,
            message,
            row,
            line,
            "^--Here",
            14 + digits + column
        );
    }

    inline static void error_report(
        std::string_view message,
        const u32 row,
        const u32 column,
        std::string_view file,
        std::string_view line
    ) {
        u32 digits = 0;
        for (u32 number = row; number > 0; number /= 10)
            digits++;

        LoggingSystem::error(
            "({}) {}.\n\n    {} | {}\n{:>{}}\n",
            file,
            message,
            row,
            line,
            "^--Here",
            14 + digits + column
        );
    }
} // namespace nk

#if NK_LOG_INFO_ENABLED == 1
    #define InfoReport(...) ::nk::info_report(__VA_ARGS__)
#else
    #define InfoReport(...)
#endif

#if NK_LOG_WARN_ENABLED == 1
    #define WarnReport(...) ::nk::warning_report(__VA_ARGS__)
#else
    #define WarnReport(...)
#endif

#define ErrorReport(...) ::nk::error_report(__VA_ARGS__)
