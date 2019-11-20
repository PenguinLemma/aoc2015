#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <unordered_map>

bool ContainsRepeatedPair(const std::string& s)
{
    // for each pair of consecutive letters, we save the last position
    // in which they were found
    std::unordered_map<std::string, int> last_position_pair;
    for (int i = 0; i < static_cast<int>(s.size()) - 1; ++i) {
        std::string pair = s.substr(i, 2);
        auto pair_and_pos = last_position_pair.find(pair);
        if (pair_and_pos != last_position_pair.end() and pair_and_pos->second < i - 1)
            return true;
        last_position_pair[pair] = i;
    }
    return false;
}

// returns true if there is a subsequence of the type 'aba'
bool ContainsABATypeSubsequence(const std::string& s)
{
    for (int i = 0; i < static_cast<int>(s.size()) - 2; ++i) {
        if (s[i] == s[i + 2])
            return true;
    }
    return false;
}

bool IsNice(const std::string& s)
{
    if (not ContainsABATypeSubsequence(s))
        return false;  // but I'm sure you are nice according to some other criteria

    if (not ContainsRepeatedPair(s))
        return false;  // but I'm sure you are nice according to some other criteria

    // Such a nice string *.*
    return true;
}

int main()
{
    std::cout << std::accumulate(std::istream_iterator<std::string>(std::cin),
                                 std::istream_iterator<std::string>(),
                                 0,
                                 [](int nice_words, const std::string& s) {
                                     return IsNice(s) ? nice_words + 1 : nice_words;
                                 })
              << std::endl;
}