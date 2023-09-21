#pragma once

#include "core/map_macro.h"

#define NK_TOKEN_GET_TYPE(token, ...) token
#define NK_TOKEN_GET_TYPE_TO_STRING(token, ...) #token
#define NK_TOKEN_GET_BYTE(x, ...) 1 << (Token::x)
#define NK_TOKEN_TYPES(...)                                                    \
    enum { MAP_LIST(NK_TOKEN_GET_TYPE, __VA_ARGS__) };                         \
    static constexpr const char* token_names[Token::TypeLength + 1] = {        \
        MAP_LIST(NK_TOKEN_GET_TYPE_TO_STRING, __VA_ARGS__)}

namespace nk {
    class Token {
    public:
        using TokenType = u32;
        NK_TOKEN_TYPES(
            Invalid,
            EndOfFile,
            NewLine,

            // Single-character tokens
            OpenParen,
            CloseParen,
            OpenBrace,
            CloseBrace,
            Comma,
            Dot,
            Semicolon,

            // One or two character tokens
            Colon,
            ColonColon,
            Bang,
            BangEqual,
            Equal,
            EqualEqual,
            Greater,
            GreaterEqual,
            Less,
            LessEqual,
            Pipe,
            PipePipe,
            And,
            AndAnd,
            Slash,
            SlashEqual,
            Percent,
            PercentEqual,
            Star,
            StarEqual,
            Plus,
            PlusEqual,
            PlusPlus,
            Minus,
            MinusEqual,
            MinusMinus,

            // Keywords
            Type,
            If,
            Else,
            True,
            False,
            Func,
            For,
            Return,
            Self,
            Mut,

            // Types
            Float32,
            Int32,
            String,

            // Literals
            TypeLiteral,
            Identifier,
            LitString,
            LitNumber,

            TypeLength
        );

        Token() : type{Token::Invalid}, line{0}, offset{0}, length{0} {}
        Token(TokenType type, u32 line, u32 offset, u32 length)
            : type{type}, line{line}, offset{offset}, length{length} {
            AssertMsg(
                type >= Token::Invalid && type < Token::TypeLength,
                "Type should be a TokenType"
            );
        }

        Token(
            TokenType type,
            u32 line,
            u32 offset,
            u32 length,
            std::string token_value
        )
            : type{type},
              line{line},
              offset{offset},
              length{length},
              token_value{token_value} {
            AssertMsg(
                type > Token::TypeLiteral && type < Token::TypeLength,
                "Only tokens literals can be constructed with a value"
            );
        }

        bool has_value() const { return token_value.has_value(); }
        std::string value() const {
            if (token_value) {
                return *token_value;
            }
            // TODO: assert when trying to access a bad value
            return "";
        }

        std::string to_string() const { return token_names[type]; }
        static std::string to_string(TokenType token_type) {
            return token_names[token_type];
        }

        TokenType operator()() const { return type; }
        bool operator==(const Token& token) const { return type == token.type; }
        bool operator==(TokenType token_type) const {
            return type == token_type;
        }

        u32 get_line() const { return line; }

    private:
        TokenType type;
        u32 line;
        u32 offset;
        u32 length;

        std::optional<std::string> token_value;
    };
} // namespace nk
