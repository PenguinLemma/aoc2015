#include <iostream>
#include <string>

constexpr char DigitToChar(int num)
{
    if(num > 9)
    {
        std::cout << "SHIT SHIT SHIT" << std::endl;
        return 'x';
    }
    return '0' + num;
}

int main()
{
    std::string sequence;
    std::cin >> sequence;

    // We do generate new sequences 40 times
    for(int i = 0; i < 40; ++i)
    {
        std::string next = "";
        int count_equal_el = 1;
        int size = sequence.size();
        for (int pos = 1; pos < size; ++pos)
        {
            if (sequence[pos] != sequence[pos - 1])
            {
                next += DigitToChar(count_equal_el);
                next += sequence[pos-1];
                count_equal_el = 1;
            }
            else
                ++count_equal_el;
        }
        if (size > 1 and sequence[size - 1] != sequence[size - 2])
        {
            next += '1';
            next += sequence[size-1];
        }
        sequence = next;
    }
    std::cout << sequence.size() << std::endl;
}