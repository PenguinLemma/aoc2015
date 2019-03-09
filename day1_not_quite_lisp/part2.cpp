#include <iostream>
#include <numeric>
#include <iterator>
#include <algorithm>

int main()
{
    int position = 0;
    int floor = 0;
    // This can be considered twisted use of `find_if`, given that
    // elements are not considered individually in terms of the
    // the condition (since the return of the lambda depends on
    // a cummulative condition and not an isolated condition)
    std::find_if(
        std::istream_iterator<char>(std::cin),
        std::istream_iterator<char>(),
        [&position, &floor](char c){
            ++position;
            if (c == '(')
            {
                ++floor;
            }
            else
            {
                --floor;
            }
            return floor == -1;
        }
    );
    std::cout << position << std::endl;
}