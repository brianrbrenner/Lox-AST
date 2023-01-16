#include "Parser.hpp"
#include "Expr/Expr.hpp"
#include "Expr/ExprVisitor.hpp"
#include "Token.hpp"
#include "TokenType.hpp"
#include <algorithm>
#include <iterator>
#include <memory>

namespace Lox {
Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)){};

std::unique_ptr<Expr> Parser::factor() {
  auto expr = unary();

  while (match(TokenType::SLASH, TokenType::STAR)) {
    auto op = previous();
    auto right = unary();
    expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
  }

  return expr;
}

std::unique_ptr<Expr> Parser::unary() {
  if (match(TokenType::BANG, TokenType::MINUS)) {
    auto op = previous();
    auto right = unary();
    return std::make_unique<UnaryExpr>(op, std::move(right));
  }

  return primary();
}

std::unique_ptr<Expr> Parser::comparison() {
  auto expr = term();

  while (match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS,
               TokenType::LESS_EQUAL)) {
    auto op = previous();
    auto right = term();
    expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
  }

  return expr;
}

std::unique_ptr<Expr> Parser::equality() {
  auto expr = comparison();

  while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
    auto op = previous();
    auto right = comparison();
    expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
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
  if (!isAtEnd()) {
    current++;
  }
  return previous();
}

bool Parser::isAtEnd() { return peek().getType() == TokenType::TokenEOF; }

Token Parser::peek() const { return tokens.at(current); }

Token Parser::previous() const { return tokens.at(current - 1); }

std::unique_ptr<Expr> Parser::primary() {
  if (match(TokenType::FALSE))
    return std::make_unique<LiteralExpr>(false);
  if (match(TokenType::TRUE))
    return std::make_unique<LiteralExpr>(true);
  if (match(TokenType::NIL))
    return std::make_unique<LiteralExpr>(nullptr);

  if (match(TokenType::NUMBER, TokenType::STRING)) {
    return std::make_unique<LiteralExpr>(previous().literalToString);
  }

  if (match(TokenType::LEFT_PAREN)) {
      auto expr = expression();
      consume(TokenType::RIGHT_PAREN, "Expect ')' after expression");
      return std::make_unique<GroupingExpr>(expr);
  }
}

std::unique_ptr<Expr> Parser::expression() { return equality(); }

std::unique_ptr<Expr> Parser::term() {
  auto expr = factor();

  while (match(TokenType::MINUS, TokenType::PLUS)) {
    auto op = previous();
    auto right = factor();
    expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
  }

  return expr;
}

} // namespace Lox
