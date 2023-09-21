#pragma once

#include "core/json.h"
#include "core/token.h"

namespace nk {
    struct Expr {
        virtual ~Expr(){};
        virtual json to_json() const = 0;
    };

    struct BinaryOp : public Expr {
        Expr* left;
        Token op;
        Expr* right;
        BinaryOp(Expr* left, Token op, Expr* right)
            : left{left}, op{op}, right{right} {}
        virtual json to_json() const override {
            return {
                {    "kind",       "BinaryOp"},
                {"operator",   op.to_string()},
                {    "left",  left->to_json()},
                {   "right", right->to_json()},
            };
        }
    };

    struct UnaryOp : public Expr {
        Token op;
        Expr* right;
        UnaryOp(Token op, Expr* right) : op{op}, right{right} {}
        virtual json to_json() const override {
            return {
                {    "kind",        "UnaryOp"},
                {"operator",   op.to_string()},
                {   "right", right->to_json()},
            };
        }
    };

    struct Grouping : public Expr {
        Expr* expression;
        Grouping(Expr* expression) : expression{expression} {}
        virtual json to_json() const override {
            return {
                {      "kind",            "Grouping"},
                {"expression", expression->to_json()},
            };
        }
    };

    struct NumericLit : public Expr {
        Token::TokenType type;
        std::string value;
        NumericLit(Token::TokenType type, std::string value)
            : type{type}, value{value} {}
        virtual json to_json() const override {
            json numeric_value;
            switch (type) {
                case Token::Int32:
                    numeric_value = {"value", std::stoi(value)};
                    break;
                case Token::Float32:
                    numeric_value = {"value", std::stof(value)};
                    break;
                default: Assert("Invalid numeric literal type");
            }
            return {
                {"kind",           "NumericLit"},
                {"type", Token::to_string(type)},
                numeric_value
            };
        }
    };

    struct StringLit : public Expr {
        std::string value;
        StringLit(std::string value) : value{value} {}
        virtual json to_json() const override {
            return {
                { "kind", "StringLit"},
                {"value",       value},
            };
        }
    };

    struct BoolLit : public Expr {
        bool value;
        BoolLit(bool value) : value{value} {}
        virtual json to_json() const override {
            return {
                { "kind", "BoolLit"},
                {"value",     value}
            };
        }
    };
} // namespace nk
