#ifndef EXPR_VISIT
#define EXPR_VISIT

namespace Lox {
class AssignExpr;
class BinaryExpr;
class CallExpr;
class GroupingExpr;
class LogicalExpr;
class LiteralExpr;
class UnaryExpr;
class VarExpr;

template<typename T>
class ExprVisitor {
public:
    ~ExprVisitor() = default;

    virtual T visitAssignExpr(const AssignExpr& expr) = 0;
    virtual T visitBinaryExpr(const BinaryExpr& expr) = 0;
    virtual T visitCallExpr(const CallExpr& expr) = 0;
    virtual T visitGroupingExpr(const GroupingExpr& expr) = 0;
    virtual T visitLogicalExpr(const LogicalExpr& expr) = 0;
    virtual T visitLiteralExpr(const LiteralExpr& expr) = 0;
    virtual T visitUnaryExpr(const UnaryExpr& expr) = 0;
    virtual T visitVarExpr(const VarExpr& expr) = 0;
};
}

#endif
