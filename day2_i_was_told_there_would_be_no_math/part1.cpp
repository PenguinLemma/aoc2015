#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>
#include "common_day2.hpp"

int ComputeWrappingPaperArea(const std::string& box_dim)
{
    std::vector<int> dimensions = plemma::GetDimensionsFromString(box_dim);
    return 3 * dimensions[0] * dimensions[1] + 2 * dimensions[1] * dimensions[2] +
           2 * dimensions[2] * dimensions[0];
}

int main()
{
    std::cout << std::accumulate(std::istream_iterator<std::string>(std::cin),
                                 std::istream_iterator<std::string>(),
                                 0,
                                 [](long long area, const std::string& box_dim) {
                                     return area + ComputeWrappingPaperArea(box_dim);
                                 })
              << std::endl;
}