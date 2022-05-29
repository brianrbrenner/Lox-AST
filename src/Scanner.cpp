#include "Scanner.hpp"
#include "Token.hpp"
#include "Lox.hpp"

#include <string>
#include <vector>

namespace Lox {

Scanner::Scanner(std::string source) {
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

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    tokens.emplace_back(TokenType EOF, "", line);
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

    addToken(NUMBER, std::stod(source.substr(start, current - start)));
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
    addToken(STRING, value);
}

void Scanner::identifier() {
    while (isAlphaNumeric(peek())) {
        advance();
    }

    const auto text = source.substr(start, current - start);
    const auto it = keywords.find(text);
    if (it != keywords.end()) {
        addToken(it->second);
    } else {
        addToken(TokenType::IDENTIFIER);
    }
}

char Scanner::advance() {
    return source.at(current++);
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
    if (isAtEnd()) return false;
    if (source.at(current) != expected) return false;

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
            addToken(LEFT_PAREN); break;
        case ')':
            addToken(RIGHT_PAREN); break;
        case '{':
            addToken(LEFT_BRACE); break;
        case '}':
            addToken(RIGHT_BRACE); break;
        case ',':
            addToken(COMMA); break;
        case '.':
            addToken(DOT); break;
        case '-':
            addToken(MINUS); break;
        case '+':
            addToken(PLUS); break;
        case ';':
            addToken(SEMICOLON); break;
        case '*':
            addToken(STAR); break; 
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
            break;
        case '/':
            if (match('/')) {
                // A comment goes until the end of the line.
                while(peek() != '\n' && !isAtEnd()) {
                    advance();
                }
            } else {
                addToken(SLASH);
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
