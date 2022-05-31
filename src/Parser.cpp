#include "Parser.hpp"

namespace Lox{
Parser::Parser(std::vector<Token> tokens): tokens(std::move(tokens)) {};

std::unique_ptr<Expr> Parser::expression() {
    return equality();
}
std::unique_ptr<Expr> Parser::equality() {
    auto expr = comparison();

    while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
        auto op = previous();
        auto right = comparison();
        auto expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) {
        return false;
    }
    return peek().getType() == type;
}

Token Parser::advance() {
    if(!isAtEnd()) {
        current++;
    }
    return previous();
}


}
