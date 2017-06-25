/*
    Equivalently, consider a sequence a with a_1 = 1. For a_{i + 1}, where i >=
    1, the possible values are a_{i} + a_{j} where j = 1, 2, ..., i.

    We are looking for sequences such that the last element is equal to k for k =
    1, .., 200. m(k) corresponds to 1 less than the shortest sequence we can
    find.

    Our search will be conducted using depth first search with a dynamically
    imposed limit on the length of the sequence. This limit is reduced whenever
    a valid sequence with a shorted length is found. To speed things up, we
    consider a_j starting from the largest element first. This is so that
    shorter sequences can be found faster, and thus the length limit can be
    reduced faster.
*/

#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>

void search(std::vector<int> const &exponents, int target_exponent, int &length_limit, std::vector<std::vector<int>> &results)
{
    if (exponents.size() >= length_limit)
        return;

    if (exponents.back() == target_exponent)
    {
        length_limit = std::min(length_limit, (int)exponents.size());
        results.emplace_back(exponents);
        return;
    }

    std::vector<int> exponents_sorted(exponents);
    std::sort(exponents_sorted.rbegin(), exponents_sorted.rend());

    for (int &exponent : exponents_sorted)
    {
        int next_exponent = exponents.back() + exponent;
        if (next_exponent <= target_exponent)
        {
            std::vector<int> _exponents(exponents);
            _exponents.emplace_back(next_exponent);
            search(_exponents, target_exponent, length_limit, results);
        }
    }
}

int main()
{
    int s = 0;
    for (int k = 1; k <= 200; k++)
    {
        std::vector<int> exponents = { 1 };
        int length_limit = INT_MAX;
        std::vector<std::vector<int>> results;
        search(exponents, k, length_limit, results);

        int length_min = INT_MAX;
        for (std::vector<int> &result : results)
            length_min = std::min(length_min, (int)result.size());

        s += length_min - 1;
    }

    std::cout << s;
}
