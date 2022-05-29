#include "Token.hpp"

Lox::Token::Token(TokenType type, const std::string lexeme, any literal, int line) {
    this.type = type;
    this.lexeme = lexeme;
    this.literal = literal;
    this.line = line;
}

Lox::Token::toString() {
    return type + " " + lexeme + " " + literal;
}
