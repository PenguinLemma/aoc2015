#include <iostream>
#include <string>
#include "look_and_say.hpp"

int main()
{
    std::string sequence;
    std::cin >> sequence;

    if (plemma::day10::LookAndSay(sequence, 50))
        std::cout << sequence.size() << std::endl;
    else
        std::cout << "Elves are discussing about the rules of the game, better come back later"
                  << std::endl;
}
