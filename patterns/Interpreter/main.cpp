#include <iostream>
#include <string>
#include "parser.h"

int main() {
    Parser parser;

    // Пример использования
    std::string expression1 = "10 + 5";
    Expression* expr1 = parser.parse(expression1);
    if (expr1) {
        std::cout << expression1 << " = " << expr1->interpret() << std::endl;
        delete expr1;
    }

    std::string expression2 = "20 - 7";
    Expression* expr2 = parser.parse(expression2);
    if (expr2) {
        std::cout << expression2 << " = " << expr2->interpret() << std::endl;
        delete expr2;
    }

    std::string expression3 = "3 * 4";
    Expression* expr3 = parser.parse(expression3);
    if (expr3) {
        std::cout << expression3 << " = " << expr3->interpret() << std::endl;
        delete expr3;
    }

     std::string expression4 = "15 / 3";
    Expression* expr4 = parser.parse(expression4);
    if (expr4) {
        std::cout << expression4 << " = " << expr4->interpret() << std::endl;
        delete expr4;
    }


    std::string expression5 = "10 / 0"; // Пример деления на ноль
    Expression* expr5 = parser.parse(expression5);
    if (expr5) {
        std::cout << expression5 << " = " << expr5->interpret() << std::endl;
        delete expr5;
    }


    std::string expression6 = "10 $ 5"; // Пример неверного оператора
    Expression* expr6 = parser.parse(expression6);
    if (expr6) {
        std::cout << expression6 << " = " << expr6->interpret() << std::endl;
        delete expr6;
    }

    return 0;
}