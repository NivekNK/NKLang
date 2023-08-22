#include "nkpch.h"

#include "core/lexer.h"

namespace nk {
    void Lexer::init(std::string input) {
        this->position = 0;
        this->read_position = 0;
        this->ch = 0;
        this->input = input;
        read_char();
    }

    Token Lexer::next_token() {
        skip_whitespace();

        Token token;
        switch (ch) {
            case '=': token = Token::Assign; break;
            case '+': token = Token::Plus; break;
            case '(': token = Token::OpenParen; break;
            case ')': token = Token::CloseParen; break;
            case '{': token = Token::OpenBrace; break;
            case '}': token = Token::CloseBrace; break;
            case ',': token = Token::Comma; break;
            case ';': token = Token::Semicolon; break;
            case ':': token = Token::Colon; break;
            case 0: token = Token::Eof; break;
            default: {
                if (is_alpha(ch)) {
                    auto identifier = read_identifier();
                    if (identifier == "func") {
                        return Token::Func;
                    } else if (identifier == "return") {
                        return Token::Return;
                    } else if (identifier == "int") {
                        return Token::Int32;
                    } else {
                        return Token(Token::Identifier, identifier);
                    }
                } else if (is_digit(ch)) {
                    auto digit = read_integer();
                    return Token(Token::LitInt32, digit);
                } else if (ch == '"') {
                    auto string = read_string();
                    return Token(Token::LitString, string);
                } else {
                    token = Token::Invalid;
                }
            }
        }

        read_char();
        return token;
    }

    void Lexer::read_char() {
        if (read_position >= input.length()) {
            ch = 0;
        } else {
            ch = input[read_position];
        }

        position = read_position;
        read_position++;
    }

    void Lexer::skip_whitespace() {
        while (is_whitespace(ch)) {
            read_char();
        }
    }

    std::string Lexer::read_identifier() {
        auto pos = position;
        while (is_alpha_numeric(ch)) {
            read_char();
        }
        return input.substr(pos, position - pos);
    }

    std::string Lexer::read_integer() {
        auto pos = position;
        while (is_digit(ch)) {
            read_char();
        }
        return input.substr(pos, position - pos);
    }

    std::string Lexer::read_string() {
        read_char();
        auto pos = position;
        while (ch != '"') {
            read_char();
        }
        read_char();
        return input.substr(pos, position - 1 - pos);
    }
} // namespace nk
