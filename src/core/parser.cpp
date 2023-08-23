#include "nkpch.h"

#include "core/parser.h"

namespace nk {
    Parser::Parser() { lexer = new Lexer(); }

    Parser::~Parser() { delete lexer; }

    Program* Parser::parse(std::string input) {
        this->input = input;
        lexer->init(input, "test.nk");

        lookahead = lexer->next_token();

        Expression* expr;
        auto lookahead_type = this->lookahead();
        switch (lookahead_type) {
            case Token::LitInt32: {
                auto token = eat(lookahead_type);
                expr = new NumericLiteral(token.value());
                break;
            }
            case Token::LitString: {
                auto token = eat(lookahead_type);
                expr = new StringLiteral(token.value());
                break;
            }
            default:
                std::cout << "Unexpected token: " << lookahead.to_string()
                          << std::endl;
                exit(1);
        }

        return new Program(expr);
    }

    Token Parser::eat(Token::TokenType token_type) {
        auto current_token = lookahead;
        if (lookahead == token_type) {
            lookahead = lexer->next_token();
            return current_token;
        }

        std::cout << "Unexpected token: " << lookahead.to_string()
                  << ", expected: " << Token::to_string(token_type)
                  << std::endl;
        exit(1);
    }
} // namespace nk
