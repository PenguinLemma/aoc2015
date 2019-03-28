#pragma once

#include <string>
#include <vector>
#include <variant>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>

namespace plemma
{

// a symbol can be saved as a string (variable name, operation)
// or a literal value (the number itself)
using Symbol = typename std::variant<std::string, uint16_t>;

char GetFirstLetter(const Symbol& s)
{
    return std::visit([](auto&& arg) -> char { return arg[0]; }, s);
}

bool IsOperation(const Symbol& s)
{
    if (not std::holds_alternative<std::string>(s))
        return false;
    char first = GetFirstLetter(s);
    return 'A' <= first and first <= 'Z';
}

Symbol GetSymbolFromString(const std::string& raw_symbol)
{
    Symbol s;
    if ('0' <= raw_symbol[0] and raw_symbol[0] <= '9')
    {
        s = std::accumulate(
                std::begin(raw_symbol),
                std::end(raw_symbol),
                0,
                [](uint16_t num_value, char c){
                    return 10*num_value + static_cast<uint16_t>(c - '0');
                }
        );
    }
    else
    {
        s = raw_symbol;
    }
    return s;
}

struct Expression
{
    std::vector<Symbol> symbols;
    uint16_t value;
    bool has_been_evaluated;

    Expression(const std::string& raw_expression)
    {
        has_been_evaluated = false;
        auto whitespace_pos = std::find(std::begin(raw_expression), std::end(raw_expression), ' ');
        while (whitespace_pos != std::end(raw_expression))
        {
            std::string raw_symbol;
            std::copy(std::begin(raw_expression), whitespace_pos, std::begin(raw_symbol));
            Symbol symbol = GetSymbolFromString(raw_symbol);
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
                [](const Symbol& s){ return IsOperation(s); }
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
    void Add(const std::string& variable, const std::string& raw_expression)
    {
        equations_[variable] = Expression(raw_expression);
    }
    uint16_t Evaluate(const Symbol& variable);
private:
    std::unordered_map<std::string, Expression> equations_;
};

uint16_t Evaluator::Evaluate(const Symbol& s)
{
    // if the symbol holds a number, we simply return it
    if(std::holds_alternative<uint16_t>(s))
    {
        return s;
    }
    // if it has already been evaluated, we return its value
    if(equations_[s].has_been_evaluated)
    {
        return equations_[s].value;
    }

    uint16_t value;
    if(equations_[s].symbols.size() == 1)
    {
        value = equations_[s].symbols[0];
    }
    else
    {
        // first symbol in the expression is the operator, and
        // its first letter will let us know which one is it
        switch(equations_[s].symbols[0][0])
        {
        case 'N':
            value = std::bit_not(Evaluate(equations_[s].symbols[1]));
            break;
        case 'A':
            value = std::bit_and(Evaluate(equations_[s].symbols[1]),
                                 Evaluate(equations_[s].symbols[2]));
            break;
        case 'O':
            value = std::bit_or(Evaluate(equations_[s].symbols[1]),
                                Evaluate(equations_[s].symbols[2]));
            break;
        case 'L':
            value = Evaluate(equations_[s].symbols[1])
                << Evaluate(equations_[s].symbols[2]);
            break;
        case 'R':
            value = Evaluate(equations_[s].symbols[1])
                >> Evaluate(equations_[s].symbols[2]);
        }
    }

    equations_[s].has_been_evaluated = true;
    equations_[s].value = value;
    return value;
}

} // namespace plemma