#include "nkpch.h"

#include "core/lexer.h"

namespace nk {
    Lexer::Lexer(std::string input)
        : position(0), read_position(0), ch(0), input(input) {
        read_char();
    }

    std::optional<Token> Lexer::next_token() {
        skip_whitespace();

        Token token;
        switch (ch) {
            case '=': token = Token::Assign; break;
            case '+': token = Token::Plus; break;
            case '(': token = Token::LParen; break;
            case ')': token = Token::RParen; break;
            case '{': token = Token::LBrace; break;
            case '}': token = Token::RBrace; break;
            case ',': token = Token::Comma; break;
            case ';': token = Token::Semicolon; break;
            case ':': token = Token::Colon; break;
            case 0: token = Token::Eof; break;
            default: {
                if (std::isalpha(ch) || ch == '_') {
                    auto identifier = read_identifier();
                    if (identifier == "func") {
                        return Token::Func;
                    } else if (identifier == "return") {
                        return Token::Return;
                    } else if (identifier == "int") {
                        return Token::Int32;
                    } else {
                        return Token::Identifier(identifier);
                    }
                } else if (std::isdigit(ch)) {
                    auto digit = read_integer();
                    return Token::Integer(digit);
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
        while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
            read_char();
        }
    }

    std::string Lexer::read_identifier() {
        auto pos = position;
        while (std::isalpha(ch) || ch == '_') {
            read_char();
        }
        return input.substr(pos, position - pos);
    }

    std::string Lexer::read_integer() {
        auto pos = position;
        while (std::isdigit(ch)) {
            read_char();
        }
        return input.substr(pos, position - pos);
    }
} // namespace nk
