#pragma once

#include <iostream>
#include <string>

namespace plemma
{
namespace day10
{

constexpr char DigitToChar(int num)
{
    if(num > 9)
    {
        std::cout << "Counter has two digits, behaviour undefined" << std::endl;
        return 'x';
    }
    return '0' + num;
}

bool LookAndSay(std::string& seq, int num_iterations)
{
    for(int i = 0; i < num_iterations; ++i)
    {
        std::string next = "";
        int count_equal_el = 1;
        int size = seq.size();
        for (int pos = 1; pos < size; ++pos)
        {
            if (seq[pos] != seq[pos - 1])
            {
                char count = DigitToChar(count_equal_el);
                if (count == 'x')
                    return false;
                next += count;
                next += seq[pos-1];
                count_equal_el = 1;
            }
            else
                ++count_equal_el;
        }
        if (size > 1 and seq[size - 1] != seq[size - 2])
        {
            next += '1';
            next += seq[size-1];
        }
        seq = next;
    }
    return true;
}

} // namespace day10
} // namespace plemma
