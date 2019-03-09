#include <iostream>
#include <numeric>
#include <iterator>
#include <algorithm>

int main()
{
    int position = 0;
    int floor = 0;
    std::find_if(
        std::istream_iterator<char>(std::cin),
        std::istream_iterator<char>(),
        [&position, &floor](char c){
            ++position;
            floor = (c == '(') ? floor + 1 : floor - 1;
            return floor == -1;
        }
    );
    std::cout << position << std::endl;
}