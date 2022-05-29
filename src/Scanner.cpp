#include "Scanner.hpp"

#include <string>
#include <vector>

namespace Lox {

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    tokens.emplace_back(EOF, "", line);
    return tokens;
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

void Scanner::addToken(TokenType type) {
    tokens.emplace_back(type, source.substr(start, current - start), line);
}

void Scanner::addToken(TokenType type, std::any literal) {
    tokens.emplace_back(type, source.substr(start, current - start), literal, line);
}

char Scanner::advance() {
    return source.at(current++);
}

void Scanner::scanToken() {
    char c = advance();
    switch(c) {
      case '(': addToken(LEFT_PAREN); break;
      case ')': addToken(RIGHT_PAREN); break;
      case '{': addToken(LEFT_BRACE); break;
      case '}': addToken(RIGHT_BRACE); break;
      case ',': addToken(COMMA); break;
      case '.': addToken(DOT); break;
      case '-': addToken(MINUS); break;
      case '+': addToken(PLUS); break;
      case ';': addToken(SEMICOLON); break;
      case '*': addToken(STAR); break; 
    }
}
}
