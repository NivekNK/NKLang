#include "nkpch.h"

#include "core/lexer.h"
#include "core/parser.h"

void get_next_token() {
    std::string input = "=+(){},;";

    auto tokens = std::vector<nk::Token>{
        nk::Token::Assign,
        nk::Token::Plus,
        nk::Token::OpenParen,
        nk::Token::CloseParen,
        nk::Token::OpenBrace,
        nk::Token::CloseBrace,
        nk::Token::Comma,
        nk::Token::Semicolon,
    };

    auto lexer = new nk::Lexer();
    lexer->init(input);
    for (auto token : tokens) {
        auto next_token = lexer->next_token();
        if (token == next_token) {
            std::cout << "expected: " << token.to_string()
                      << ", received: " << next_token.to_string() << std::endl;
        } else {
            std::cout << "ERROR: expected: " << token.to_string()
                      << ", received: " << next_token.to_string() << std::endl;
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
        nk::Token(nk::Token::Identifier, "five"),
        nk::Token::Colon,
        nk::Token::Int32,
        nk::Token::Assign,
        nk::Token(nk::Token::LitInt32, "5"),
        nk::Token::Semicolon,

        nk::Token(nk::Token::Identifier, "ten"),
        nk::Token::Colon,
        nk::Token::Int32,
        nk::Token::Assign,
        nk::Token(nk::Token::LitInt32, "10"),
        nk::Token::Semicolon,

        nk::Token(nk::Token::Identifier, "add"),
        nk::Token::Colon,
        nk::Token::Int32,
        nk::Token::Func,

        nk::Token::OpenParen,
        nk::Token(nk::Token::Identifier, "x"),
        nk::Token::Colon,
        nk::Token::Int32,
        nk::Token::Comma,
        nk::Token(nk::Token::Identifier, "y"),
        nk::Token::Colon,
        nk::Token::Int32,
        nk::Token::CloseParen,

        nk::Token::OpenBrace,
        nk::Token::Return,
        nk::Token(nk::Token::Identifier, "x"),
        nk::Token::Plus,
        nk::Token(nk::Token::Identifier, "y"),
        nk::Token::Semicolon,
        nk::Token::CloseBrace,

        nk::Token(nk::Token::Identifier, "result"),
        nk::Token::Colon,
        nk::Token::Assign,
        nk::Token(nk::Token::Identifier, "add"),
        nk::Token::OpenParen,
        nk::Token(nk::Token::Identifier, "five"),
        nk::Token::Comma,
        nk::Token(nk::Token::Identifier, "ten"),
        nk::Token::CloseParen,
        nk::Token::Semicolon,
    };

    auto lexer = new nk::Lexer();
    lexer->init(input);
    for (auto token : tokens) {
        auto next_token = lexer->next_token();
        if (token == next_token) {
            std::cout << "expected: " << token.to_string()
                      << ", received: " << next_token.to_string() << std::endl;
        } else {
            std::cout << "ERROR: expected: " << token.to_string()
                      << ", received: " << next_token.to_string() << std::endl;
        }
    }

    delete lexer;
}

int main(void) {
    auto parser = new nk::Parser();
    auto program = "42";
    auto ast = parser->parse(program);

    std::cout << ast->to_json().dump(4) << std::endl;

    delete ast;
    delete parser;

    // get_next_token();
    // get_full_lexer();
    return 0;
}
