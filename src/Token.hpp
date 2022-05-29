#ifndef TOKEN
#define TOKEN

#include "TokenType.hpp"
#include <string>
#include <any>

namespace Lox
{
class Token {
    public:
        Token(TokenType, std::string, any, int);
        std::string toString();
    private:
        enum TokenType type; 
        std::string lexeme;
        std::any literal;
        int line;
};
}

#endif 
