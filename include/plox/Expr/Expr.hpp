#ifndef EXPR
#define EXPR

#include "ExprVisitor.hpp"
#include <any>

namespace Lox {
class Expr {
public:
    virtual ~Expr () = default;

    virtual std::any accept(ExprVisitor<std::any>& visitor) const = 0;
};
}

#endif
