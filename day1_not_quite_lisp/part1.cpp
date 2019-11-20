#include <iostream>
#include <iterator>
#include <numeric>

int main()
{
    std::cout << std::accumulate(
                     std::istream_iterator<char>(std::cin),
                     std::istream_iterator<char>(),
                     0,
                     [](int floor, char c) { return (c == '(') ? floor + 1 : floor - 1; })
              << std::endl;
}