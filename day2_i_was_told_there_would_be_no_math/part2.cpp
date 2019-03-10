#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include "common_day2.hpp"

int ComputeRibbonLength(const std::string& box_dim)
{
    std::vector<int> dimensions = plemma::GetDimensionsFromString(box_dim);
    return 2 * dimensions[0] + 2 * dimensions[1] + // perimeter of smalles face of box
           dimensions[0] * dimensions[1] * dimensions[2]; // volum of the box
}

int main()
{
    std::cout <<
    std::accumulate(
        std::istream_iterator<std::string>(std::cin),
        std::istream_iterator<std::string>(),
        0,
        [](long long length, const std::string& box_dim){ return length + ComputeRibbonLength(box_dim); }
    )
    << std::endl;
}