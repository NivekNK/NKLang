#pragma once

/** @file */

#if defined(NK_DEBUG) || defined(NK_RELEASE_DEBUG_INFO)
    #define NK_ENABLE_ASSERTS 1
#endif

#if NK_ENABLE_ASSERTS == 1

namespace nk {
    /**
     * @brief Assert class used for line breaks while debuggin the application.
     */
    class Assert {
    public:
        /**
         * @brief Print message of the assertion on console with the logger API.
         * @param expression The assertion expression converted to string.
         * @param message Message to print when the assertion fails.
         * @param file File where the assertion ocurrs.
         * @param line Line number where the assertion ocurrs.
         */
        static inline void report_assert_failure(
            std::string_view expression,
            std::string_view message,
            std::string_view file,
            const u32 line
        ) {
            if (!message.empty()) {
                if (LoggingSystem::is_initialized()) {
                    FatalLog(
                        "Assertion Failure: {}, message: '{}', in file: {}, "
                        "line: {}",
                        expression,
                        message,
                        file,
                        line
                    );
                } else {
                    std::cout << std::format(
                                     "Assertion Failure: {}, message: '{}', in "
                                     "file: {}, line: {}",
                                     expression,
                                     message,
                                     file,
                                     line
                                 )
                              << std::endl;
                }
            } else {
                if (LoggingSystem::is_initialized()) {
                    FatalLog(
                        "Assertion Failure: {}, in file: {}, line: {}",
                        expression,
                        file,
                        line
                    );
                } else {
                    std::cout
                        << std::format(
                               "Assertion Failure: {}, in file: {}, line: {}",
                               expression,
                               file,
                               line
                           )
                        << std::endl;
                }
            }
        }

        /**
         * @brief Line break for assertions (supports Linux and Windows).
         */
        static inline void debug_break() {
    #if defined(NK_PLATFORM_LINUX)
            __builtin_trap();
    #elif defined(NK_PLATFORM_WINDOWS)
            __debugbreak();
    #else
            if (Logger::is_initialized()) {
                CoreFatal("NKEngine only supports Windows and Linux!");
            } else {
                std::cout << "NKEngine only supports Windows and Linux!"
                          << std::endl;
            }
    #endif
        }
    };
} // namespace nk

    /**
     * @brief Assertion with message.
     */
    #define AssertMsg(expr, message)                                           \
        {                                                                      \
            if (expr) {                                                        \
            } else {                                                           \
                nk::Assert::report_assert_failure(                            \
                    #expr, message, __FILE__, __LINE__                         \
                );                                                             \
                nk::Assert::debug_break();                                    \
            }                                                                  \
        }
    /**
     * @brief Assertion with no message.
     */
    #define Assert(expr) AssertMsg(expr, "")
    /**
     * @brief Assertion with no message. Keeps the expression on the line of the
     * assertion.
     */
    #define AssertKeep(expr) Assert(expr)
    /**
     * @brief Assertion with message. Keeps the expression on the line of the
     * assertion.
     */
    #define AssertKeepMsg(expr, message) AssertMsg(expr, message)

#else

    #define Assert(expr)
    #define AssertMsg(expr, message)
    #define AssertKeep(expr) expr
    #define AssertKeepMsg(expr, message) expr

#endif
