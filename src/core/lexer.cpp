#include "nkpch.h"

#include "core/lexer.h"

#include "core/error_handling.h"
#include "core/token_keyword_map.h"

namespace nk {
    void Lexer::init(std::string input, std::string file) {
        this->position = 0;
        this->read_position = 0;
        this->ch = 0;
        this->file = file;
        this->input = input;
        read_char();
    }

    Token Lexer::next_token() {
        skip_whitespace();
        skip_comment();

        Token token;
        switch (ch) {
            case 0: {
                token = Token(Token::EndOfFile, line, position, 0);
                break;
            }
            case '(': {
                token = Token(Token::OpenParen, line, position, 1);
                break;
            }
            case ')': {
                token = Token(Token::CloseParen, line, position, 1);
                break;
            }
            case '{': {
                token = Token(Token::OpenBrace, line, position, 1);
                break;
            }
            case '}': {
                token = Token(Token::CloseBrace, line, position, 1);
                break;
            }
            case ',': {
                token = Token(Token::Comma, line, position, 1);
                break;
            }
            case '.': {
                token = Token(Token::Dot, line, position, 1);
                break;
            }
            case ';': {
                token = Token(Token::Semicolon, line, position, 1);
                break;
            }
            case ':': {
                read_match(':', Token::Colon, Token::ColonColon, token);
                break;
            }
            case '!': {
                read_match('=', Token::Bang, Token::BangEqual, token);
                break;
            }
            case '=': {
                read_match('=', Token::Equal, Token::EqualEqual, token);
                break;
            }
            case '>': {
                read_match('=', Token::Greater, Token::GreaterEqual, token);
                break;
            }
            case '<': {
                read_match('=', Token::Less, Token::LessEqual, token);
                break;
            }
            case '|': {
                read_match('|', Token::Pipe, Token::PipePipe, token);
                break;
            }
            case '&': {
                read_match('&', Token::And, Token::AndAnd, token);
                break;
            }
            case '/': {
                read_match('=', Token::Slash, Token::SlashEqual, token);
                break;
            }
            case '%': {
                read_match('=', Token::Percent, Token::PercentEqual, token);
                break;
            }
            case '*': {
                read_match('=', Token::Star, Token::StarEqual, token);
                break;
            }
            case '+': {
                if (match('=')) {
                    token = Token(Token::PlusEqual, line, position, 2);
                    read_char();
                } else if (match('+')) {
                    token = Token(Token::PlusPlus, line, position, 2);
                    read_char();
                } else {
                    token = Token(Token::Plus, line, position, 1);
                }
                break;
            }
            case '-': {
                if (match('=')) {
                    token = Token(Token::MinusEqual, line, position, 2);
                    read_char();
                } else if (match('-')) {
                    token = Token(Token::MinusMinus, line, position, 2);
                    read_char();
                } else {
                    token = Token(Token::Minus, line, position, 1);
                }
                break;
            }
            case '"': {
                read_string(token);
                return token;
            }
            default: {
                if (is_digit(ch)) {
                    read_number(token);
                    return token;
                } else if (is_alpha(ch)) {
                    read_identifier_or_keyword(token);
                    return token;
                } else {
                    std::string current_line;
                    ErrorReport(
                        "Unexpected character",
                        line,
                        get_line_and_column(current_line),
                        file,
                        current_line
                    );
                    token = Token();
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
            if (ch == '\n')
                line++;
            read_char();
        }
    }

    void Lexer::skip_comment() {
        while (ch == '/' && read_position < input.length() &&
               input[read_position] == '/') {
            while (ch != '\n') {
                read_char();
            }
            skip_whitespace();
        }
    }

    void Lexer::read_identifier_or_keyword(Token& token) {
        auto pos = position;
        while (is_alpha_numeric(ch)) {
            read_char();
        }

        std::string text = input.substr(pos, position - pos);
        const TokenKeyword* keyword =
            TokenKeywordMap::is_valid_keyword(text.c_str(), text.length());

        if (keyword == nullptr) {
            token =
                Token(Token::Identifier, line, position, text.length(), text);
            return;
        }

        switch (keyword->token) {
            // Keywords
            case Token::Type:
                token = Token(Token::Type, line, position, text.length());
                break;
            case Token::If:
                token = Token(Token::If, line, position, text.length());
                break;
            case Token::Else:
                token = Token(Token::Else, line, position, text.length());
                break;
            case Token::True:
                token = Token(Token::True, line, position, text.length());
                break;
            case Token::False:
                token = Token(Token::False, line, position, text.length());
                break;
            case Token::Func:
                token = Token(Token::Func, line, position, text.length());
                break;
            case Token::For:
                token = Token(Token::For, line, position, text.length());
                break;
            case Token::Return:
                token = Token(Token::Return, line, position, text.length());
                break;
            case Token::Self:
                token = Token(Token::Self, line, position, text.length());
                break;
            case Token::Mut:
                token = Token(Token::Mut, line, position, text.length());
                break;

            // Types
            case Token::Float32:
                token = Token(Token::Float32, line, position, text.length());
                break;
            case Token::Int32:
                token = Token(Token::Int32, line, position, text.length());
                break;
            case Token::String:
                token = Token(Token::String, line, position, text.length());
                break;

            default:
                token = Token(
                    Token::Identifier, line, position, text.length(), text
                );
        }
    }

    void Lexer::read_number(Token& token) {
        auto pos = position;
        while (is_digit(ch))
            read_char();

        if (ch == '.' && is_digit(input[read_position])) {
            read_char();

            while (is_digit(ch))
                read_char();
        }

        std::string number = input.substr(pos, position - pos);
        token =
            Token(Token::LitNumber, line, position, number.length(), number);
    }

    void Lexer::read_string(Token& token) {
        // TODO: make so the first character of a multiline string
        // is what commands the start of the column for the string

        read_char();
        auto pos = position;
        while (ch != '"' && ch != 0) {
            if (ch == '\n')
                line++;
            read_char();
        }

        if (ch == 0) {
            std::string current_line;
            ErrorReport(
                "Unterminated string",
                line,
                get_line_and_column(current_line),
                file,
                current_line
            );
            token = Token();
            return;
        }

        read_char();
        std::string string = input.substr(pos, position - 1 - pos);
        token = Token(
            Token::LitString, line, position, string.length() + 2, string
        );
    }

    bool Lexer::match(char match_char) const {
        return read_position < input.length() &&
               input[read_position] == match_char;
    }

    void Lexer::read_match(
        char match_char,
        Token::TokenType single,
        Token::TokenType combination,
        Token& token
    ) {
        if (!match(match_char)) {
            token = Token(single, line, position, 1);
            return;
        }

        token = Token(combination, line, position, 2);
        read_char();
    }

    u32 Lexer::get_line_and_column(std::string& out_line) const {
        u32 current_line = 1;
        u32 current_column = 1;

        for (u32 i = 0; i < input.length(); i++) {
            char c = input[i];

            if (c == '\r')
                continue;

            if (c == '\n') {
                current_line++;
                current_column = 1;
                continue;
            }

            if (current_line == line) {
                out_line += c;
                if (i == position) {
                    return current_column;
                }
            }

            current_column++;
        }

        return 0;
    }
} // namespace nk
