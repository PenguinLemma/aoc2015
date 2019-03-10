#pragma once

#include <vector>
#include <string>
#include <functional>

namespace plemma
{

class Position2D
{
public:
    Position2D(int posx, int posy) : x(posx), y(posy) {}
    int X() const { return x; }
    int Y() const { return y; }
    void PerformDrunkElfsDirective(char directive);
private:
    int x;
    int y;
};

void Position2D::PerformDrunkElfsDirective(char directive)
{
    switch(directive)
    {
        case '^' : ++y; break;
        case '>' : ++x; break;
        case 'v' : --y; break;
        case '<' : --x; break;
    }
}

// hasher to be able to use std::unordered_set<Position2D>
struct Position2DHasher
{
    std::size_t operator()(const Position2D& pos) const
    {
        auto hasher1D = std::hash<int>();
        auto first = hasher1D(pos.X());
        return first ^ (hasher1D(pos.Y()) + 0x9e3779b9 + (first << 6) + (first >> 2));
    }
};

// comparator to be able to use std::unordered_set<Position2D>
struct Position2DComparator
{
    bool operator()(const Position2D& lhs, const Position2D& rhs) const
    {
        return (lhs.X() == rhs.X()) and (lhs.Y() == rhs.Y());
    }
};

} // namespace plemma