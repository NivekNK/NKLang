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
        std::string read_string();

    private:
        bool is_whitespace(char c) const {
            return c == ' ' || c == '\t' || c == '\n' || c == '\r' ||
                   c == '\f' || c == '\v';
        }
        bool is_alpha(char c) const {
            return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
        }
        bool is_digit(char c) const { return c >= '0' && c <= '9'; }
        bool is_alpha_numeric(char c) const {
            return is_alpha(c) || is_digit(c);
        }

        u32 position;
        u32 read_position;
        char ch;
        std::string input;
    };
} // namespace nk
