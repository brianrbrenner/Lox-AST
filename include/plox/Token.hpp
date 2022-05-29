#ifndef TOKEN
#define TOKEN

#include "TokenType.hpp"
#include <string>
#include <any>

namespace Lox
{
class Token {
    public:
        Token();
        Token(TokenType, std::string, int);
        Token(TokenType, std::string, std::any, int);
        std::string toString();
        std::string literalToString();
    private:
        enum TokenType type; 
        std::string lexeme;
        std::any literal;
        int line;
};
}

#endif 
