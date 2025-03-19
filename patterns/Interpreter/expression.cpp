#include "expression.h"
#include <iostream>

NumberExpression::NumberExpression(int num) : number(num) {}

int NumberExpression::interpret() {
    return number;
}

AddExpression::AddExpression(Expression* left_expr, Expression* right_expr) : left(left_expr), right(right_expr) {}

AddExpression::~AddExpression() {
    delete left;
    delete right;
}

int AddExpression::interpret() {
    return left->interpret() + right->interpret();
}

SubtractExpression::SubtractExpression(Expression* left_expr, Expression* right_expr) : left(left_expr), right(right_expr) {}

SubtractExpression::~SubtractExpression() {
    delete left;
    delete right;
}

int SubtractExpression::interpret() {
    return left->interpret() - right->interpret();
}

MultiplyExpression::MultiplyExpression(Expression* left_expr, Expression* right_expr) : left(left_expr), right(right_expr) {}

MultiplyExpression::~MultiplyExpression() {
    delete left;
    delete right;
}

int MultiplyExpression::interpret() {
    return left->interpret() * right->interpret();
}

DivideExpression::DivideExpression(Expression* left_expr, Expression* right_expr) : left(left_expr), right(right_expr) {}

DivideExpression::~DivideExpression() {
    delete left;
    delete right;
}

int DivideExpression::interpret() {
    int right_val = right->interpret();
    if (right_val == 0) {
        std::cerr << "Ошибка: деление на ноль!" << std::endl;
        return 0; // Или можно бросить исключение
    }
    return left->interpret() / right_val;
}