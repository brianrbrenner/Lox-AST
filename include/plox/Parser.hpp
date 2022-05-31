#include "TokenType.hpp"
#include "Token.hpp"
#include "Expr/Expr.hpp"

#include <vector>
#include <memory>

namespace Lox {
class Parser {
public:
    Parser(std::vector<Token>);

private:
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> equality();
    std::vector<Token> tokens;

    template<typename...Type>
    bool match(Type... types);

    Token peek() const;
    Token advance();

    bool isAtEnd();
    bool check(TokenType);
    int current = 0;
};

template<typename...Type>
bool Parser::match(Type... types) {
    std::initializer_list<bool> values{check(types)...};
    for (auto i : values) {
        if (i) {
            advance();
            return true;
        }
    }
    return false;
}
}
