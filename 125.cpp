/*
    This is straightforward. The only thing that requires concern is that some
    palindromes can be written in more than one way as sum of consecutive squares,
    so there is a need to check for duplicates.
*/

#include <iostream>
#include <unordered_set>
#include <cmath>
#include <numeric>
#include "string_util.h"

typedef unsigned long long ull;

ull get_sum(int a, int b)
{
    return (b * (b + 1) * (2 * b + 1) - (a - 1) * (a) * (2 * a - 1)) / 6;
}

int main()
{
    std::unordered_set<ull> numbers;
    int a = 1;
    while (get_sum(a, a + 1) < std::pow(10, 8))
    {
        int b = a + 1;
        ull s = get_sum(a, b);
        while (s < std::pow(10, 8))
        {
            if (util::is_palindrome(std::to_string(s)))
                numbers.emplace(s);
            b++;
            s = get_sum(a, b);
        }
        a++;
    }

    std::cout << std::accumulate(numbers.begin(), numbers.end(), ull(0));
}
