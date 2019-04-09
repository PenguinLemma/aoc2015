#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>

namespace plemma
{

inline bool IsOperation(const std::string& s)
{
    return 'A' <= s[0] and s[0] <= 'Z';
}

struct Expression
{
    std::vector<std::string> symbols;
    uint16_t value;
    bool has_been_evaluated;

    Expression(){}

    Expression(const std::string& raw_expression)
    {
        has_been_evaluated = false;
        auto whitespace_pos = std::find(std::begin(raw_expression), std::end(raw_expression), ' ');
        while (whitespace_pos != std::end(raw_expression))
        {
            std::string symbol;
            std::copy(std::begin(raw_expression), whitespace_pos, std::begin(symbol));
            symbols.push_back(symbol);
            whitespace_pos = std::find(std::next(whitespace_pos), std::end(raw_expression), ' ');
        }

        // If there are more than 1 symbols, one of them must
        // be an operation. We place the operation in the first
        // position.
        if (symbols.size() > 1)
        {
            auto it_operator = find_if(
                std::begin(symbols),
                std::end(symbols),
                [](const std::string& s){ return IsOperation(s); }
            );
            std::rotate(
                std::begin(symbols),
                it_operator,
                it_operator
            );
        }
    }
};

class Evaluator
{
public:
    // Adds a variable to the equations' map from its raw expression (rhs)
    void Add(const std::string& variable, const std::string& raw_expression)
    {
        equations_[variable] = Expression(raw_expression);
    }

    // Evaluates a symbol, that can be a variable or a number
    uint16_t Evaluate(const std::string& symbol);
private:
    std::unordered_map<std::string, Expression> equations_;
};

uint16_t Evaluator::Evaluate(const std::string& symbol)
{
    // if the symbol holds a number, we simply return it
    if(std::isdigit(symbol[0]))
    {
        return static_cast<uint16_t>(std::stoi(symbol));
    }

    Expression rhs = equations_[symbol];
    // if it has already been evaluated, we return its value
    if(rhs.has_been_evaluated)
    {
        return rhs.value;
    }

    uint16_t value;
    if(rhs.symbols.size() == 1)
    {
        value = Evaluate(rhs.symbols[0]);
    }
    else
    {
        // first symbol in the expression is the operator, and
        // its first letter will let us know which one is it
        switch(rhs.symbols[0][0])
        {
        case 'N':
            value = std::bit_not{}(Evaluate(rhs.symbols[1]));
            break;
        case 'A':
            value = std::bit_and{}(Evaluate(rhs.symbols[1]),
                                 Evaluate(rhs.symbols[2]));
            break;
        case 'O':
            value = std::bit_or{}(Evaluate(rhs.symbols[1]),
                                Evaluate(rhs.symbols[2]));
            break;
        case 'L':
            value = Evaluate(rhs.symbols[1])
                << Evaluate(rhs.symbols[2]);
            break;
        case 'R':
            value = Evaluate(rhs.symbols[1])
                >> Evaluate(rhs.symbols[2]);
        }
    }

    equations_[symbol].has_been_evaluated = true;
    equations_[symbol].value = value;
    return value;
}

} // namespace plemma