#include "Token.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace Lox {
class Scanner {
public:
    Scanner(std::string source);
    std::vector<Token> scanTokens();

private:
    void scanToken();
    void addToken(TokenType);
    void addToken(TokenType, std::any);
    void string();
    void number();
    void identifier();
    char advance();
    char peek() const;
    char peekNext() const;
    bool isAtEnd() const;
    bool isDigit(char);
    bool isAlpha(char);
    bool isAlphaNumeric(char);
    bool match(char);

    std::unordered_map<std::string, TokenType> keywords;
    std::vector<Token> tokens;
    std::string source;
    int start = 0;
    int current = 0;
    int line = 1;
};
}
