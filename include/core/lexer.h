#pragma once

#include "core/token.h"

namespace nk {
    class Lexer {
    public:
        Lexer(std::string input);

        std::optional<Token> next_token();
        void read_char();
        void skip_whitespace();

        std::string read_identifier();
        std::string read_integer();

    private:
        u32 position;
        u32 read_position;
        char ch;
        std::string input;
    };
} // namespace nk
