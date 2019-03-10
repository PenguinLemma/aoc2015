#include <iostream>
#include <unordered_set>
#include "position2d.hpp"

int main()
{
    using plemma::Position2D;
    using plemma::Position2DHasher;
    using plemma::Position2DComparator;
    char dir;
    Position2D position_santa(0,0);
    Position2D position_robosanta(0,0);
    std::unordered_set<Position2D, Position2DHasher, Position2DComparator>
        visited_houses{ position_santa };

    bool is_santas_turn = true;
    while (std::cin >> dir)
    {
        if (is_santas_turn)
        {
            position_santa.PerformDrunkElfsDirective(dir);
            visited_houses.insert(position_santa);
        }
        else
        {
            position_robosanta.PerformDrunkElfsDirective(dir);
            visited_houses.insert(position_robosanta);
        }
        is_santas_turn = !is_santas_turn;
    }
    std::cout << visited_houses.size() << std::endl;
}