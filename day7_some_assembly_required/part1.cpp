#include <iostream>
#include <string>
#include "evaluator.hpp"

#include <fstream>

// To solve this problem, I find it easier to reformulate
// it as variables and expressions. For example, I will
// translate `lf AND lq -> ls` as `ls = ls AND lq`. This
// way, to find the signal that a certain wire will contain,
// I will be evaluating the expression assigned to the
// variable with the name of the wire.

int main()
{
    plemma::Evaluator evaluator;
    std::string expression;
    // use std::getline(cin, s, '-') to get the expression
    // (i.e. all the part of the line before the ->)
    // then throw away the next character (>) and then read
    // the name of the variable (last string on the line)
    while (std::getline(std::cin, expression, '-')) {
        char rubbish;
        std::cin >> rubbish;
        std::string variable_name;
        std::cin >> variable_name;
        evaluator.Add(variable_name, expression);
        std::getline(std::cin, expression);
    }
    std::cout << evaluator.Evaluate("a") << std::endl;
}