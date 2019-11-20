#include <cctype>
#include <iostream>
#include <optional>

std::optional<int> toNumber(char c)
{
    if (c == '-')
        return std::optional<int>(-1);
    return (c >= '0' && c <= '9') ? std::optional<int>(static_cast<int>(c - '0')) : std::nullopt;
}

int main()
{
    char c;
    long long int sum = 0;
    long long int partial_sum = 0;
    int sign = 1;

    while (std::cin >> c) {
        if (auto num = toNumber(c)) {
            if (num.value() == -1)
                sign = -1;
            else
                partial_sum = 10 * partial_sum + num.value();
        }
        else {
            sum += sign * partial_sum;
            partial_sum = 0;
            sign = 1;
        }
    }
    sum += partial_sum;
    std::cout << sum << std::endl;
}