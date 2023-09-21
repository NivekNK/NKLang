#include "nkpch.h"

#include "core/error_handling.h"
#include "core/parser.h"

namespace nk {
    Parser::Parser() { lexer = new Lexer(); }

    Parser::~Parser() { delete lexer; }

    Program* Parser::parse(std::string input) {
        this->input = input;

        lexer->init(input, "test.nk");
        current = lexer->next_token();

        Expr* expr = expression();
        return new Program(expr);
    }

    Token Parser::consume() {
        auto current_token = current;
        current = lexer->next_token();
        return current_token;
    }

    bool Parser::consume(Token::TokenType token, std::string_view message) {
        if (current == token) {
            current = lexer->next_token();
            return true;
        }

        std::string line;
        u32 col = lexer->get_line_and_column(line);

        std::cout << col << " " << line << std::endl;

        ErrorReport(
            message,
            current.get_line(),
            col,
            lexer->get_file(),
            line
        );
        return false;
    }

    Expr* Parser::expression() { return equality(); }

    Expr* Parser::primary() {
        switch (current()) {
            case Token::False: {
                auto expr = new BoolLit(false);
                advance();
                return expr;
            }
            case Token::True: {
                auto expr = new BoolLit(true);
                advance();
                return expr;
            }
            case Token::LitNumber: {
                auto expr = new NumericLit(Token::Int32, current.value());
                advance();
                return expr;
            }
            case Token::LitString: {
                auto expr = new StringLit(current.value());
                advance();
                return expr;
            }
            case Token::OpenParen: {
                advance();
                Expr* expr = expression();
                consume(Token::CloseParen, "Expect ')' after expression");
                return new Grouping(expr);
            }
            default:
                std::string line;
                ErrorReport(
                    "Expect expression",
                    current.get_line(),
                    lexer->get_line_and_column(line),
                    lexer->get_file(),
                    line
                );
                return nullptr;
        }
    }

    Expr* Parser::unary() {
        match(
            {
                Token op = consume();
                Expr* right = unary();
                return new UnaryOp(op, right);
            },
            Token::Bang,
            Token::Minus
        );
        return primary();
    }

    Expr* Parser::factor() {
        Expr* expr = unary();

        while_match(
            {
                Token op = consume();
                Expr* right = unary();
                expr = new BinaryOp(expr, op, right);
            },
            Token::Slash,
            Token::Star
        );

        return expr;
    }

    Expr* Parser::term() {
        Expr* expr = factor();

        while_match(
            {
                Token op = consume();
                Expr* right = factor();
                expr = new BinaryOp(expr, op, right);
            },
            Token::Minus,
            Token::Plus
        );

        return expr;
    }

    Expr* Parser::comparison() {
        Expr* expr = term();

        while_match(
            {
                Token op = consume();
                Expr* right = term();
                expr = new BinaryOp(expr, op, right);
            },
            Token::Greater,
            Token::GreaterEqual,
            Token::Less,
            Token::LessEqual
        );

        return expr;
    }

    Expr* Parser::equality() {
        Expr* expr = comparison();

        while_match(
            {
                Token op = consume();
                Expr* right = comparison();
                expr = new BinaryOp(expr, op, right);
            },
            Token::BangEqual,
            Token::EqualEqual
        );

        return expr;
    }
} // namespace nk
