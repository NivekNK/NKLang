#pragma once

#include "core/token.h"

namespace nk {
    class Lexer {
    public:
        Lexer() : position(0), read_position(0), ch(0) {}

        void init(std::string input);
        Token next_token();
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
