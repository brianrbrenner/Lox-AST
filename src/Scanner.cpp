#include "Scanner.hpp"
#include "Token.hpp"
#include "Lox.hpp"

#include <string>
#include <vector>

namespace Lox {

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    tokens.emplace_back(TokenType EOF, "", line);
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

char Scanner::peek(){
    if (isAtEnd()) return '\0';
    return source.at(current);
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source.at(current) != expected) return false;

    ++current;
    return true;
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
        // unhandled character
        default:
            Lox::Error(line, "Unexpected character.");
            break;
    }
}
}
