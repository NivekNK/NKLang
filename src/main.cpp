#include "core/token.h"
#include "nkpch.h"

#include "core/lexer.h"

void get_next_token() {
    std::string input = "=+(){},;";

    auto tokens = std::vector<nk::Token>{
        nk::Token::Assign, nk::Token::Plus,      nk::Token::LParen,
        nk::Token::RParen, nk::Token::LBrace,    nk::Token::RBrace,
        nk::Token::Comma,  nk::Token::Semicolon,
    };

    auto lexer = new nk::Lexer(input);
    for (auto token : tokens) {
        auto next_token = lexer->next_token();
        if (token == next_token.value()) {
            std::cout << "expected: " << token.to_string()
                      << ", received: " << next_token->to_string() << std::endl;
        } else {
            std::cout << "ERROR: expected: " << token.to_string()
                      << ", received: " << next_token->to_string() << std::endl;

        }
    }

    delete lexer;
}

void get_full_lexer() {
    std::string input = R"(
five: int = 5;
ten: int = 10;
add: int func(x: int, y: int) {
    return x + y;
}
result := add(five, ten);
)";

    auto tokens = std::vector<nk::Token>{
        nk::Token::Identifier("five"),
        nk::Token::Colon,
        nk::Token::Int32,
        nk::Token::Assign,
        nk::Token::Integer("5"),
        nk::Token::Semicolon,

        nk::Token::Identifier("ten"),
        nk::Token::Colon,
        nk::Token::Int32,
        nk::Token::Assign,
        nk::Token::Integer("10"),
        nk::Token::Semicolon,

        nk::Token::Identifier("add"),
        nk::Token::Colon,
        nk::Token::Int32,
        nk::Token::Func,

        nk::Token::LParen,
        nk::Token::Identifier("x"),
        nk::Token::Colon,
        nk::Token::Int32,
        nk::Token::Comma,
        nk::Token::Identifier("y"),
        nk::Token::Colon,
        nk::Token::Int32,
        nk::Token::RParen,

        nk::Token::LBrace,
        nk::Token::Return,
        nk::Token::Identifier("x"),
        nk::Token::Plus,
        nk::Token::Identifier("y"),
        nk::Token::Semicolon,
        nk::Token::RBrace,

        nk::Token::Identifier("result"),
        nk::Token::Colon,
        nk::Token::Assign,
        nk::Token::Identifier("add"),
        nk::Token::LParen,
        nk::Token::Identifier("five"),
        nk::Token::Comma,
        nk::Token::Identifier("ten"),
        nk::Token::RParen,
        nk::Token::Semicolon,
    };

    auto lexer = new nk::Lexer(input);
    for (auto token : tokens) {
        auto next_token = lexer->next_token();
        if (token == next_token.value()) {
            std::cout << "expected: " << token.to_string()
                      << ", received: " << next_token->to_string() << std::endl;
        } else {
            std::cout << "ERROR: expected: " << token.to_string()
                      << ", received: " << next_token->to_string() << std::endl;

        }
    }

    delete lexer;
}

int main(void) {
    // get_next_token();
    get_full_lexer();
    return 0;
}
