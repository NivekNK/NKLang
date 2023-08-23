#pragma once

#include "core/token.h"

namespace nk {
    class Lexer {
    public:
        Lexer() : position{0}, read_position{0}, ch{0}, line{1} {}

        void init(std::string input, std::string file);
        Token next_token();

    private:
        void read_char();

        std::string read_identifier();
        void read_string(Token& token);
        void read_number(Token& token);
        void read_match(
            char match_char,
            Token::TokenType single,
            Token::TokenType combination,
            Token& token
        );

        void skip_whitespace();
        void skip_comment();

        bool match(char match_char) const;

        bool is_whitespace(char c) const {
            return c == ' ' || c == '\t' || c == '\n' || c == '\r' ||
                   c == '\f' || c == '\v';
        }
        bool is_digit(char c) const { return c >= '0' && c <= '9'; }
        bool is_alpha(char c) const {
            return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
        }
        bool is_alpha_numeric(char c) const {
            return is_alpha(c) || is_digit(c);
        }

        u32 get_line_and_column(std::string& line) const;

        u32 position;
        u32 read_position;
        char ch;
        u32 line;
        std::string file;
        std::string input;
    };
} // namespace nk
