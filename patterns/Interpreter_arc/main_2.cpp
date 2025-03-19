#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

// Абстрактный класс выражения
class Expression {
public:
    virtual int interpret() = 0;
    virtual ~Expression() = default;
};

// Терминальное выражение для чисел
class Number : public Expression {
    int value;
public:
    explicit Number(int v) : value(v) {}
    int interpret() override { return value; }
};

// Нетерминальное выражение для сложения
class Add : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
public:
    Add(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)) {}
    int interpret() override { return left->interpret() + right->interpret(); }
};

// Нетерминальное выражение для вычитания
class Subtract : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
public:
    Subtract(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)) {}
    int interpret() override { return left->interpret() - right->interpret(); }
};

// Класс парсера для построения AST
class Parser {
    std::vector<std::string> tokens;
    size_t pos = 0;

    std::unique_ptr<Expression> parseExpression() {
        auto left = parseTerm();
        while (pos < tokens.size()) {
            std::string op = tokens[pos];
            if (op == "+" || op == "-") {
                pos++;
                auto right = parseTerm();
                if (op == "+") {
                    left = std::make_unique<Add>(std::move(left), std::move(right));
                } else {
                    left = std::make_unique<Subtract>(std::move(left), std::move(right));
                }
            } else {
                break;
            }
        }
        return left;
    }

    std::unique_ptr<Expression> parseTerm() {
        std::string token = tokens[pos++];
        return std::make_unique<Number>(std::stoi(token));
    }

public:
    explicit Parser(const std::string& input) {
        std::istringstream iss(input);
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
    }

    std::unique_ptr<Expression> parse() {
        return parseExpression();
    }
};

int main() {
    std::string expression = "5 + 3 - 2 + 7 - 1 + 1";
    
    Parser parser(expression);
    auto ast = parser.parse();
    
    std::cout << "Результат вычисления '" << expression << "' = " 
              << ast->interpret() << std::endl;

    return 0;
}