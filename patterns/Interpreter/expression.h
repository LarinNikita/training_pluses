#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

class Expression {
public:
    virtual ~Expression() {}
    virtual int interpret() = 0;
};

class NumberExpression : public Expression {
private:
    int number;

public:
    NumberExpression(int num);
    int interpret() override;
};

class AddExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    AddExpression(Expression* left_expr, Expression* right_expr);
    ~AddExpression();
    int interpret() override;
};

class SubtractExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    SubtractExpression(Expression* left_expr, Expression* right_expr);
    ~SubtractExpression();
    int interpret() override;
};

class MultiplyExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    MultiplyExpression(Expression* left_expr, Expression* right_expr);
    ~MultiplyExpression();
    int interpret() override;
};

class DivideExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    DivideExpression(Expression* left_expr, Expression* right_expr);
    ~DivideExpression();
    int interpret() override;
};

#endif // EXPRESSION_H