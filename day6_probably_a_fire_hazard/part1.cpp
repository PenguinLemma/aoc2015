#include <bitset>
#include <iostream>

namespace plemma {

enum class Option { kTurnOff = 0, kTurnOn = 1, kToggle = 2 };

constexpr size_t kNumColumns = 1000;
constexpr size_t kNumRows = 1000;
constexpr size_t kNumLights = kNumRows * kNumColumns;

using Grid = typename std::bitset<kNumLights>;

struct Parameters
{
    size_t start_row;
    size_t start_col;
    size_t end_row;
    size_t end_col;
    Option option;
};

bool ReadParametersOfCommand(Parameters& param)
{
    std::string s;
    if (!(std::cin >> s))
        return false;
    if (s[s.size() - 1] == 'n') {
        std::cin >> s;
        if (s[s.size() - 1] == 'n') {
            param.option = Option::kTurnOn;
        }
        else {
            param.option = Option::kTurnOff;
        }
    }
    else {
        param.option = Option::kToggle;
    }
    char comma;
    std::cin >> param.start_row >> comma >> param.start_col;
    std::cin >> s;
    std::cin >> param.end_row >> comma >> param.end_col;
    // read "through"
    ++param.end_row;
    ++param.end_col;
    return true;
}

constexpr size_t Compute1DIndex(size_t row, size_t col)
{
    return row * kNumColumns + col;
}

void ExecuteCommand(Grid& grid, Parameters& param)
{
    for (size_t row = param.start_row; row < param.end_row; ++row) {
        for (size_t col = param.start_col; col < param.end_col; ++col) {
            size_t position = Compute1DIndex(row, col);
            switch (param.option) {
                case Option::kTurnOff:
                    grid.reset(position);
                    break;
                case Option::kTurnOn:
                    grid.set(position);
                    break;
                case Option::kToggle:
                    grid.flip(position);
            }
        }
    }
}

}  // namespace plemma

int main()
{
    plemma::Grid grid;

    plemma::Parameters p;

    while (plemma::ReadParametersOfCommand(p)) {
        plemma::ExecuteCommand(grid, p);
    }
    std::cout << grid.count() << std::endl;
}