#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

int ComputeWrappingPaperArea(const std::string& box_dim)
{
    std::vector<int> dimensions(3, 0);
    int index_dim = 0;
    for (int i = 0; i < static_cast<int>(box_dim.size()); ++i)
    {
        if (box_dim[i] == 'x')
        {
            ++index_dim;
        }
        else
        {
            dimensions[index_dim] *= 10;
            dimensions[index_dim] += static_cast<int>(box_dim[i]) - static_cast<int>('0');
        }
    }
    // Put biggest element in the last position of the vector so that the first
    // two elements correspond to the face of the box with the smallest area
    std::nth_element(std::begin(dimensions), std::begin(dimensions) + 2, std::end(dimensions));
    return 3 * dimensions[0] * dimensions[1] +
           2 * dimensions[1] * dimensions[2] +
           2 * dimensions[2] * dimensions[0];
}

int main()
{
    std::cout <<
    std::accumulate(
        std::istream_iterator<std::string>(std::cin),
        std::istream_iterator<std::string>(),
        0,
        [](long long area, const std::string& box_dim){ return area + ComputeWrappingPaperArea(box_dim); }
    )
    << std::endl;
}