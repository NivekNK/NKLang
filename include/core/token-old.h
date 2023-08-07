#pragma once

#include <format>
#include <string>
#include <variant>

namespace nk {
    struct Token {
    private:
        struct VariantEqualVisitor {
            template<typename T>
            bool operator()(const T& lhs, const T& rhs) const {
                return lhs == rhs;
            }
            template<typename T, typename U>
            bool operator()(const T&, const U&) const {
                return false;
            }
        };
        struct VariantEqualTypeVisitor {
            template<typename T>
            bool operator()(const T&, const T&) const {
                return true;
            }
            template<typename T, typename U>
            bool operator()(const T&, const U&) const {
                return false;
            }
        };
        template<typename... Types>
        bool are_variants_equal(
            const std::variant<Types...>& lhs, const std::variant<Types...>& rhs
        ) const {
            if (lhs.index() != rhs.index()) {
                return false;
            }
            return std::visit(VariantEqualVisitor{}, lhs, rhs);
        }
        template<typename... Types>
        bool are_variants_equal_type(
            const std::variant<Types...>& lhs, const std::variant<Types...>& rhs
        ) const {
            if (lhs.index() != rhs.index()) {
                return false;
            }
            return std::visit(VariantEqualTypeVisitor{}, lhs, rhs);
        }

    public:
        struct Invalid {
            bool operator==(const Invalid&) const { return true; }
            std::string to_string() const { return "Invalid"; }
        };
        struct Number {
            std::string value;
            bool operator==(const Number& rhs) const {
                return value == rhs.value;
            }
            std::string to_string() const {
                return "Number"
                       " (" +
                       std ::format("{}", value) + ")";
            }
        };
        using TokenType = std::variant<Invalid, Number>;
        Token() : value{Invalid()} {}
        Token(Invalid value) : value(value) {}
        Token(Number value) : value(value) {}
        bool operator==(const Token& rhs) const {
            return are_variants_equal(value, rhs.value);
        }
        bool equal_type(const Token& rhs) const {
            return are_variants_equal_type(value, rhs.value);
        }
        std ::string to_string() const {
            return std::visit(
                [](auto&& value) -> std ::string { return value.to_string(); },
                value
            );
        }

    private:
        TokenType value;
    };
} // namespace nk
