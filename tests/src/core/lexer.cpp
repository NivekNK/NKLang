#include <gtest/gtest.h>

#include "nkpch.h"
#include "core/lexer.h"

TEST(Lexer, GetNextToken) {
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
        auto current_token = lexer->next_token();
        EXPECT_EQ(current_token, token);
    }

    delete lexer;
}

TEST(Lexer, GetNextTokenExtended) {
    std::string input = R"V0G0N(
            five: int = 5;
            ten: int = 10;

            add: int func(x: int, y: int) {
                return x + y;
            }

            result := add(five, ten);
        )V0G0N";

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
        auto current_token = lexer->next_token();
        EXPECT_EQ(current_token, token);
    }

    delete lexer;
}
