#include <iostream>

// Solution that won't make a twisted use of STL algorithms
int main()
{
    int position = 1;
    int floor = 0;
    char c;
    while (std::cin >> c) {
        if (c == '(') {
            ++floor;
        }
        else {
            --floor;
        }
        if (floor == -1)
            break;

        ++position;
    }
    std::cout << position << std::endl;
}