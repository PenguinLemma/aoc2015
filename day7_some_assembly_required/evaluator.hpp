#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include <iostream>

namespace plemma {

inline bool IsOperation(const std::string& s)
{
    return 'A' <= s[0] and s[0] <= 'Z';
}

struct Expression
{
    std::vector<std::string> symbols;
    std::optional<uint16_t> value;

    Expression() = default;

    explicit Expression(const std::string& raw_expression)
    {
        value = std::nullopt;
        auto start = std::cbegin(raw_expression);
        auto whitespace_pos =
            std::find(std::cbegin(raw_expression), std::cend(raw_expression), ' ');
        while (whitespace_pos != std::end(raw_expression)) {
            symbols.push_back({start, whitespace_pos});
            start = std::next(whitespace_pos);
            whitespace_pos = std::find(start, std::cend(raw_expression), ' ');
        }

        // If there are more than 1 symbols, one of them must
        // be an operation. We place the operation in the first
        // position.
        if (symbols.size() > 1) {
            auto it_operator = find_if(std::begin(symbols),
                                       std::end(symbols),
                                       [](const std::string& s) { return IsOperation(s); });
            std::rotate(std::begin(symbols), it_operator, std::next(it_operator));
        }
    }

    explicit Expression(uint16_t val) : symbols{std::to_string(val)}, value{val} {}

    void ResetValue() { value = std::nullopt; }
};  // namespace plemma

class Evaluator
{
  public:
    // Adds a variable to the equations' map from its raw expression (rhs)
    void Add(const std::string& variable, const std::string& raw_expression)
    {
        equations_[variable] = Expression(raw_expression);
    }

    void Add(std::string const& variable, uint16_t value)
    {
        equations_[variable] = Expression(value);
    }

    // Evaluates a symbol, that can be a variable or a number
    uint16_t Evaluate(const std::string& symbol);

    template <typename RightHandSide>
    void Overwrite(std::string const& variable, RightHandSide&& rhs);

  private:
    void Reset();
    std::unordered_map<std::string, Expression> equations_;
};

inline uint16_t Evaluator::Evaluate(const std::string& symbol)
{
    // if the symbol holds a number, we simply return it
    if (std::isdigit(symbol[0])) {
        return static_cast<uint16_t>(std::stoi(symbol));
    }

    Expression rhs = equations_[symbol];
    // if it has already been evaluated, we return its value
    if (rhs.value) {
        return rhs.value.value();
    }

    uint16_t value;
    if (rhs.symbols.size() == 1) {
        value = Evaluate(rhs.symbols[0]);
    }
    else {
        // first symbol in the expression is the operator, and
        // its first letter will let us know which one is it
        switch (rhs.symbols[0][0]) {
            case 'N':
                value = std::bit_not{}(Evaluate(rhs.symbols[1]));
                break;
            case 'A':
                value = std::bit_and{}(Evaluate(rhs.symbols[1]), Evaluate(rhs.symbols[2]));
                break;
            case 'O':
                value = std::bit_or{}(Evaluate(rhs.symbols[1]), Evaluate(rhs.symbols[2]));
                break;
            case 'L':
                value = Evaluate(rhs.symbols[1]) << Evaluate(rhs.symbols[2]);
                break;
            case 'R':
                value = Evaluate(rhs.symbols[1]) >> Evaluate(rhs.symbols[2]);
        }
    }

    equations_[symbol].value = value;
    return value;
}
template <typename RightHandSide>
inline void Evaluator::Overwrite(std::string const& variable, RightHandSide&& rhs)
{
    // We add after resetting so that if rhs is the value (uinuint16_t), it won't
    // be computed again from the expression (symbols = {to_string(value)}). But
    // we are protected against change of order of the following two lines :P
    Reset();
    Add(variable, rhs);
}

inline void Evaluator::Reset()
{
    for (auto& eq : equations_) {
        eq.second.ResetValue();
    }
}

}  // namespace plemma