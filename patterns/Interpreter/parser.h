#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "expression.h"

class Parser {
public:
    Expression* parse(const std::string& expression);
};

#endif // PARSER_H