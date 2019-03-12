#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>
#include <numeric>

bool IsVowel(const char c)
{
    return (c == 'a') or (c == 'e') or (c == 'i') or (c == 'o') or (c == 'u');
}

bool IsForbidden(const char a, const char b)
{
    return ((a == 'a') and (b == 'b'))
        or ((a == 'c') and (b == 'd'))
        or ((a == 'p') and (b == 'q'))
        or ((a == 'x') and (b == 'y'));
}

bool IsNice(const std::string& s)
{
    // check that there are 3 or more vowels
    int num_vowels = std::count_if(
                        std::begin(s),
                        std::end(s),
                        [](char c){ return IsVowel(c); }
                    );
    if (num_vowels < 3)
        return false; // but I'm sure you are nice according to some other criteria

    // check that contains at least one doubled letter
    auto adj_equal_letters = std::adjacent_find(
                                std::begin(s),
                                std::end(s),
                                [](char a, char b){ return a == b; }
                            );
    if (adj_equal_letters == std::end(s))
        return false; // but I'm sure you are nice according to some other criteria

    // check that it doesn't contain any of the forbidden pairs
    auto forbidden_pair = std::adjacent_find(
                            std::begin(s),
                            std::end(s),
                            [](char a, char b){ return IsForbidden(a,b); }
                        );
    if (forbidden_pair != std::end(s))
        return false; // but I'm sure you are nice according to some other criteria

    // Such a nice string *.*
    return true;
}

int main()
{
    std::cout <<
    std::accumulate(
        std::istream_iterator<std::string>(std::cin),
        std::istream_iterator<std::string>(),
        0,
        [](int nice_words, const std::string& s){ return IsNice(s) ? nice_words + 1 : nice_words; }
    )
    << std::endl;
}