#pragma once

#include "core/map_macro.h"

#define NK_TOKEN_GET_TYPE(token, ...) token
#define NK_TOKEN_GET_TYPE_TO_STRING(token, ...) #token
#define NK_TOKEN_TYPES(...)                                                    \
    enum { MAP_LIST(NK_TOKEN_GET_TYPE, __VA_ARGS__) };                         \
    static constexpr const char* token_names[Token::TypeLength + 1] = {        \
        MAP_LIST(NK_TOKEN_GET_TYPE_TO_STRING, __VA_ARGS__)};

namespace nk {
    class Token {
    public:
        using Type = u32;
        NK_TOKEN_TYPES(
            Return,
            Func,
            Assign,
            Plus,
            OpenParen,
            CloseParen,
            OpenBrace,
            CloseBrace,
            Comma,
            Colon,
            Semicolon,
            Eof,
            Int32,
            Invalid,
            TypeLiteral,
            LitInt32,
            Identifier,
            TypeLength
        )

        Token() = default;
        Token(Type type) : type(type) {}

        Token(Type type, std::string token_value)
            : type(type), token_value(token_value) {
            // assert(
            //     type > 32 && type < 64,
            //     "Only tokens with values can be constructed with a value"
            // );
        }

        bool has_value() const { return token_value.has_value(); }
        std::string value() const {
            if (token_value) {
                return *token_value;
            }
            // TODO: assert when trying to access a bad value
            return "";
        }

        std::string to_string() const {
            return token_names[type] + (token_value ? " " + *token_value : "");
        }
        static std::string to_string(Type token_type) {
            return token_names[token_type];
        }

        Type operator()() const { return type; }
        bool operator==(const Token& token) const { return type == token.type; }
        bool operator==(Type token_type) const { return type == token_type; }

    private:
        Type type = Token::Invalid;
        std::optional<std::string> token_value;
    };
} // namespace nk
