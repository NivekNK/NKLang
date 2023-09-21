#pragma once

#include "core/expression.h"
#include "core/lexer.h"
#include "core/map_macro.h"

#define NK_GET_PARSER_CASE(token, ...) case token:
#define while_match(task, ...)                                                 \
    {                                                                          \
        bool match = false;                                                    \
        do {                                                                   \
            switch (current()) {                                               \
                MAP(NK_GET_PARSER_CASE, __VA_ARGS__) {                         \
                    task;                        \
                    match = true;                                              \
                    break;                                                     \
                }                                                              \
                default: match = false; break;                                 \
            }                                                                  \
        } while (match);                                                       \
    }

#define match(task, ...)                                                       \
    switch (current()) {                                                       \
        MAP(NK_GET_PARSER_CASE, __VA_ARGS__) {                                 \
            task;                                \
            break;                                                             \
        }                                                                      \
        default: break;                                                        \
    }

namespace nk {
    struct Program {
        Expr* expr;
        Program(Expr* expr) : expr(expr) {}
        ~Program() { delete expr; }
        json to_json() const {
            return {
                {"kind",       "Program"},
                {"body", expr->to_json()}
            };
        }
    };

    class Parser {
    public:
        Parser();
        ~Parser();

        Program* parse(std::string input);

    private:
        bool consume(Token::TokenType token, std::string_view message);
        Token consume();
        void advance() { current = lexer->next_token(); }

        Expr* expression();
        Expr* primary();
        Expr* unary();
        Expr* factor();
        Expr* term();
        Expr* comparison();
        Expr* equality();

        std::string input;
        Lexer* lexer;

        Token current;
    };
} // namespace nk
