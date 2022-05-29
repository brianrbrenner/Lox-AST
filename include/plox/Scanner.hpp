#include "Token.hpp"

#include <string>
#include <vector>

namespace Lox {
class Scanner {
public:
    Scanner(std::string source) { this->source = source; }
    std::vector<Token> scanTokens();

private:
    void scanToken();
    char advance();
    char peek();
    bool isAtEnd();
    void addToken(TokenType);
    void addToken(TokenType, std::any);
    bool match(char);
    void string();

    std::vector<Token> tokens;
    std::string source;
    int start = 0;
    int current = 0;
    int line = 1;
};
}
