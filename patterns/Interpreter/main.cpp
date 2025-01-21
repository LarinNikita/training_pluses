#include <iostream>
#include <string>
#include <sstream>
#include <stack>

// Базовый класс для интерпретатора
class Expression {
public:
    virtual int interpret() = 0;
};

// Класс для операндов (числа)
class NumberExpression : public Expression {
private:
    int number;
public:
    NumberExpression(int num) : number(num) {}
    int interpret() override {
        return number;
    }
};

// Класс для операторов (+ и -)
class OperatorExpression : public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    OperatorExpression(Expression* left, Expression* right) : left(left), right(right) {}
};

// Класс для оператора сложения
class AddExpression : public OperatorExpression {
public:
    AddExpression(Expression* left, Expression* right) : OperatorExpression(left, right) {}
    int interpret() override {
        return left->interpret() + right->interpret();
    }
};

// Класс для оператора вычитания
class SubtractExpression : public OperatorExpression {
public:
    SubtractExpression(Expression* left, Expression* right) : OperatorExpression(left, right) {}
    int interpret() override {
        return left->interpret() - right->interpret();
    }
};

// Класс для парсера и интерпретатора математических выражений
class Interpreter {
private:
    Expression* parseExpression(const std::string& expression) const;
public:
    int evaluate(const std::string& expression) const;
};

Expression* Interpreter::parseExpression(const std::string& expression) const {
    std::stack<Expression*> stack;
    std::istringstream tokens(expression); // Инициализация istream с строкой
    std::string token;

    while (tokens >> token) { // Проверка на успешное извлечение токена
        if (isdigit(token[0])) {
            stack.push(new NumberExpression(std::stoi(token)));
        } else if (token == "+") {
            Expression* right = stack.top();
            stack.pop();
            Expression* left = stack.top();
            stack.pop();
            stack.push(new AddExpression(left, right));
        } else if (token == "-") {
            Expression* right = stack.top();
            stack.pop();
            Expression* left = stack.top();
            stack.pop();
            stack.push(new SubtractExpression(left, right));
        }
    }

    return stack.top();
}

int Interpreter::evaluate(const std::string& expression) const {
    Expression* parsedExpression = parseExpression(expression);
    int result = parsedExpression->interpret();
    delete parsedExpression;
    return result;
}

// Демонстрация работы интерпретатора
void demoInterpreter() {
    Interpreter interpreter;
    std::string expression = "7 3 - 2 1 + *"; // Эквивалентно (7 - 3) * (2 + 1) = 4 * 3 = 12
    int result = interpreter.evaluate(expression);
    std::cout << "Result of the expression '" << expression << "' is: " << result << std::endl;
}

int main() {
    demoInterpreter();
    return 0;
}