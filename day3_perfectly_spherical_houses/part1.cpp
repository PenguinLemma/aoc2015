#include <iostream>
#include <unordered_set>
#include "position2d.hpp"

int main()
{
    using plemma::Position2D;
    using plemma::Position2DComparator;
    using plemma::Position2DHasher;
    char dir;
    Position2D position_santa(0, 0);
    std::unordered_set<Position2D, Position2DHasher, Position2DComparator> visited_houses{
        position_santa};

    while (std::cin >> dir) {
        position_santa.PerformDrunkElfsDirective(dir);
        visited_houses.insert(position_santa);
    }
    std::cout << visited_houses.size() << std::endl;
}