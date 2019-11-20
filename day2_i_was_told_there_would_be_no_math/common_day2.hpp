#pragma once

#include <string>
#include <vector>

namespace plemma {

std::vector<int> GetDimensionsFromString(const std::string& box_dim)
{
    std::vector<int> dimensions(3, 0);
    int index_dim = 0;
    for (int i = 0; i < static_cast<int>(box_dim.size()); ++i) {
        if (box_dim[i] == 'x') {
            ++index_dim;
        }
        else {
            dimensions[index_dim] *= 10;
            dimensions[index_dim] += static_cast<int>(box_dim[i]) - static_cast<int>('0');
        }
    }
    // Put biggest element in the last position of the vector so that the first
    // two elements correspond to the face of the box with the smallest area
    std::nth_element(std::begin(dimensions), std::begin(dimensions) + 2, std::end(dimensions));
    return dimensions;
}

}  // namespace plemma