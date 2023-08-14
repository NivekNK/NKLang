#pragma once

#include "core/json.h"
#include "core/lexer.h"


namespace nk {
    struct Expression {
        std::string value;
        Expression(std::string value) : value(value) {}
        virtual ~Expression(){};
        virtual json to_json() const = 0;
    };

    struct Program {
        Expression* expr;
        Program(Expression* expr) : expr(expr) {}
        ~Program() { delete expr; }
        json to_json() const {
            return {
                {"type",       "Program"},
                {"body", expr->to_json()}
            };
        }
    };

    struct NumericLiteral : public Expression {
        NumericLiteral(std::string value) : Expression(value) {}
        virtual json to_json() const override {
            return {
                { "type", "NumericLiteral"},
                {"value", std::stoi(value)}
            };
        }
    };

    class Parser {
    public:
        Parser();
        ~Parser();

        Program* parse(std::string input);

    private:
        Token eat(Token::Type token);

        std::string input;
        Lexer* lexer;
        Token lookahead;
    };
} // namespace nk
