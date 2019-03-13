#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

namespace plemma
{

constexpr size_t kNumColumns = 1000;
constexpr size_t kNumRows = 1000;
constexpr size_t kNumLights = kNumRows * kNumColumns;

using Grid = typename std::vector<std::vector<int> >;

struct Parameters
{
    int brightness_diff;
    size_t start_row;
    size_t start_col;
    size_t end_row;
    size_t end_col;
};

bool ReadParametersOfCommand(Parameters& param)
{
    std::string s;
    if (!(std::cin >> s))
        return false;
    if (s[s.size() - 1] == 'n')
    {
        std::cin >> s;
        if (s[s.size() - 1] == 'n')
        {
            param.brightness_diff = 1;
        }
        else
        {
            param.brightness_diff = -1;
        }
    }
    else
    {
        param.brightness_diff = 2;
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

void ExecuteCommand(Grid& grid, Parameters& param)
{
    for(size_t row = param.start_row; row < param.end_row; ++row)
    {
        auto start = std::begin(grid[row]) + param.start_col;
        auto end = std::begin(grid[row]) + param.end_col;
        std::transform(start, end, start,
            [=](const int& value){ return std::max(0, value + param.brightness_diff); }
        );
    }
}

int AccumulateBrightness(const Grid& grid)
{
    return std::accumulate(
        std::begin(grid),
        std::end(grid),
        0,
        [](int sum, const std::vector<int>& v){
            return std::accumulate(std::begin(v), std::end(v), sum);
        }
    );
}

} // namespace plemma

int main()
{
    plemma::Grid grid(plemma::kNumRows, std::vector<int>(plemma::kNumColumns, 0));

    plemma::Parameters p;

    while(plemma::ReadParametersOfCommand(p))
    {
        plemma::ExecuteCommand(grid, p);
    }
    std::cout << plemma::AccumulateBrightness(grid) << std::endl;
}