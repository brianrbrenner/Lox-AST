#include "Scanner.hpp"
#include "Token.hpp"
#include "Lox.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace Lox {

Scanner::Scanner(std::string source) : source(std::move(source)) {
    keywords = {
        {"and", TokenType::AND},
        {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},
        {"false", TokenType::FALSE},
        {"for", TokenType::FOR},
        {"fun", TokenType::FUN},
        {"if", TokenType::IF},
        {"nil", TokenType::NIL},
        {"or", TokenType::OR},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super", TokenType::SUPER},
        {"this", TokenType::THIS},
        {"true", TokenType::TRUE},
        {"var", TokenType::VAR},
        {"while", TokenType::WHILE},
    };
} 

void Scanner::printTokens() {
    // not really working currently
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        std::cout << it->toString();
    }
}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    tokens.emplace_back(TokenType::TokenEOF, "", line);
    printTokens();
    return tokens;
}

bool Scanner::isAtEnd() const {
    return current >= static_cast<int>(source.size());
}

void Scanner::addToken(TokenType type) {
    tokens.emplace_back(type, source.substr(start, current - start), line);
}

void Scanner::addToken(TokenType type, std::any literal) {
    tokens.emplace_back(type, source.substr(start, current - start), literal, line);
}

void Scanner::number() {
    while (isDigit(peek())) {
        advance();
    }

    // Look for fractional part
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the "."
        advance();
    while (isDigit(peek())) {
            advance();
        }
    }
    
    addToken(TokenType::NUMBER, std::stod(source.substr(start, current - start)));
}

void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line ++;
        advance();
    }

    if (isAtEnd()) {
        Lox::Error(line, "Unterminated string.");
        return;
    }

    // The closing ".
    advance();

    // Trim surrounding quotes
    std::string value = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, value);
}

void Scanner::identifier() {
    while (isAlphaNumeric(peek())) {
        advance();
    }

    const auto text = source.substr(start, current - start);
    if (const auto it = keywords.find(text); it != keywords.end()) {
        addToken(it->second);
    } else {
        addToken(TokenType::IDENTIFIER);
    }
}

char Scanner::advance() {
    ++current;
    return source.at(current - 1);
}

char Scanner::peek() const {
    if (isAtEnd()) {
        return '\0';
    } 
    return source.at(current);
}

char Scanner::peekNext() const {
    if (current + 1 >= static_cast<int>(source.size())) {
        return '\0';
    }

    return source.at(current + 1);
}

bool Scanner::match(char expected) {
    if (isAtEnd()) {
        return false;
    }
    if (source.at(current) != expected) {
        return false;
    }    

    ++current;
    return true;
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

void Scanner::scanToken() {
    char c = advance();
    switch(c) {
        // single character tokens
        case '(':
            addToken(TokenType::LEFT_PAREN); break;
        case ')':
            addToken(TokenType::RIGHT_PAREN); break;
        case '{':
            addToken(TokenType::LEFT_BRACE); break;
        case '}':
            addToken(TokenType::RIGHT_BRACE); break;
        case ',':
            addToken(TokenType::COMMA); break;
        case '.':
            addToken(TokenType::DOT); break;
        case '-':
            addToken(TokenType::MINUS); break;
        case '+':
            addToken(TokenType::PLUS); break;
        case ';':
            addToken(TokenType::SEMICOLON); break;
        case '*':
            addToken(TokenType::STAR); break; 
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '/':
            if (match('/')) {
                // A comment goes until the end of the line.
                while(peek() != '\n' && !isAtEnd()) {
                    advance();
                }
            } else {
                addToken(TokenType::SLASH);
            }
        
        // whitespace
        case ' ':
        case '\r':
        case '\t':
        // Ignore whitespace.
            break;
        case '\n':
            line++;
            break;

        // string literal
        case '"':
            string();
            break;

        // number literal    
        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                identifier();
            } else {
                Lox::Error(line, "Unexpected character.");
            }
            break;
    }
}
}
