#include "nkpch.h"

#include "core/parser.h"

namespace nk {
    Parser::Parser() { lexer = new Lexer(); }

    Parser::~Parser() { delete lexer; }

    Program* Parser::parse(std::string input) {
        this->input = input;
        lexer->init(input);

        lookahead = lexer->next_token();

        auto token = eat(Token::LitInt32);
        auto expr = new NumericLiteral(token.value());

        return new Program(expr);
    }

    Token Parser::eat(Token::Type token_type) {
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
