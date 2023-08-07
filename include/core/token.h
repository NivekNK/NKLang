#pragma once

#include "core/defines.h"

namespace nk {
    class Token {
    public:
        struct NumericLiteral {
            i32 value;
            bool operator==(const NumericLiteral& rhs) const {
                return value == rhs.value;
            }
            bool operator==(i32 type) const {
                return type == Token::NumericLiteral;
            }
        };

    private:
        using Type = std::variant<i32, NumericLiteral>;
        Type type;

    public:
        Token() : type(Invalid) {}
        Token(i32 type) : type(type) {}
        Token(NumericLiteral type) : type(type) {}

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

        enum {
            Program,
            NumericLiteral,
            Invalid,
        };

        const char* token_names[Token::Invalid + 1] = {
            "Program",
            "NumericLiteral",
            "Invalid",
        };
    };
} // namespace nk
