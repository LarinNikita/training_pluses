#include "parser.h"
#include <sstream>
#include <iostream>

Expression* Parser::parse(const std::string& expression) {
    std::stringstream ss(expression);
    char op;
    int num1, num2;

    if (ss >> num1 >> op >> num2) {
        Expression* left = new NumberExpression(num1);
        Expression* right = new NumberExpression(num2);

        switch (op) {
            case '+':
                return new AddExpression(left, right);
            case '-':
                return new SubtractExpression(left, right);
            case '*':
                return new MultiplyExpression(left, right);
            case '/':
                return new DivideExpression(left, right);
            default:
                std::cerr << "Ошибка: неизвестный оператор: " << op << std::endl;
                delete left;
                delete right;
                return nullptr;
        }
    } else {
        std::cerr << "Ошибка: неверный формат выражения." << std::endl;
        return nullptr;
    }
}