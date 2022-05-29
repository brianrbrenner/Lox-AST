#include "Token.hpp"

namespace Lox {
Token::Token(TokenType type, std::string lexeme, std::any literal, int line) {
    this->type = type;
    this->lexeme = lexeme;
    this->literal = literal;
    this->line = line;
}

Token::Token(TokenType type, std::string lexeme, int line) {
    Token(type, lexeme, std::any{}, line);
}

std::string Token::toString() {
    return std::to_string(static_cast<int>(type)) + ", lexeme: '" + lexeme + "', literal: '" +
    literalToString() + "'";
}

std::string Token::literalToString() {
    switch(type) {
        case TokenType::STRING:
            return std::any_cast<std::string>(literal);
        case TokenType::NUMBER:
            return std::to_string(std::any_cast<double>(literal));
        default:
            return "";
    } 
}
}
