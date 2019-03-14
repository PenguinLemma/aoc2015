#pragma once

#include <string>
#include <vector>
#include <variant>
#include <unordered_map>
#include <algorithm>
#include <iterator>

namespace plemma
{

// a symbol can be saved as a string (variable name, operation)
// or a literal value (the number itself)
using Symbol = typename std::variant<std::string, uint16_t>;

bool IsOperation(const Symbol& s)
{
    return std::holds_alternative<std::string>(s)
        and ('A' <= s[0] and s[0] <= 'Z');
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
            std::rotate(
                std::begin(symbols),
                find_if(
                    std::begin(symbols),
                    std::end(symbols),
                    [](const Symbol& s){ return IsOperation(s); }
                ),
                std::end(symbols)
            );
        }
    }
};

class Evaluator
{
public:
    void Add(const std::string& variable, const std::string& raw_expression)
    {
        variables_[variable] = Expression(raw_expression);
    }
    Evaluate(const std::string& variable);
private:
    std::unordered_map<std::string, Expression> variables_;
};

} // namespace plemma