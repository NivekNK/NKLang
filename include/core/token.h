#pragma once

namespace nk {
    template<typename T>
    concept ToString = requires(T t) {
        { t.to_string() } -> std::same_as<std::string>;
    };

    class Token {
    public:
        struct TokenType {
            std::string value;
            TokenType(std::string value) : value(value) {}
            bool operator==(const TokenType& rhs) const {
                return value == rhs.value;
            }
            std::string to_string() const { return value; }
        };

        struct Integer : public TokenType {
            Integer(std::string value) : TokenType(value) {}
        };
        struct Identifier : public TokenType {
            Identifier(std::string value) : TokenType(value) {}
        };

    private:
        using Type = std::variant<i32, Integer, Identifier>;
        Type type;

        template<typename T>
        struct IsTokenType {
            static constexpr bool value =
                std::is_same_v<T, Integer> || std::is_same_v<T, Identifier>;
        };

    public:
        Token() : type(Token::Invalid) {}
        Token(i32 type) : type(type) {}
        template<typename T>
        Token(T type) : type(type) {
            // static_assert(IsTokenType<T>::value, "Only accept token types!");
        }

        std::string to_string() const {
            if (std::holds_alternative<i32>(this->type)) {
                return token_names[std::get<i32>(this->type)];
            }

            return std::visit(
                [](auto& type) {
                    if constexpr (ToString<decltype(type)>) {
                        return type.to_string();
                    }
                    return std::string("Error: Bad type on Token!");
                },
                type
            );
        }

        bool operator==(const Token& token) {
            if (type.index() != token.type.index()) {
                return false;
            }
            return std::visit(
                [](const auto& lhs, const auto& rhs) {
                    if constexpr (std::is_same_v<
                                      decltype(lhs), decltype(rhs)>) {
                        return lhs == rhs;
                    }
                    return false;
                },
                type, token.type
            );
        }

        bool operator==(i32 type) {
            return std::holds_alternative<i32>(this->type) &&
                   std::get<i32>(this->type) == type;
        }

        bool operator!=(const Token& token) { return !(type == token.type); }
        bool operator!=(i32 type) {
            if (std::holds_alternative<i32>(this->type))
                return std::get<i32>(this->type) != type;
            return true;
        }

        enum {
            Return,
            Func,
            Assign,
            Plus,
            LParen,
            RParen,
            LBrace,
            RBrace,
            Comma,
            Colon,
            Semicolon,
            Eof,
            Int32,
            Invalid,
        };

        const char* token_names[Token::Invalid + 1] = {
            "Return",    "Func",   "Assign", "Plus",    "LParen",
            "RParen",    "LBrace", "RBrace", "Comma",   "Colon",
            "Semicolon", "Eof",    "Int32",  "Invalid",
        };
    };
} // namespace nk
