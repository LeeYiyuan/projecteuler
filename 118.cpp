/*
    For each permutation of 1, 2, ..., 9, we loop through the combinations of
    slices such that each slice is a prime number. The valid slice combinations
    are collected and the count of unique slice combinations is taken as the
    answer.
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <numeric>
#include "prime_util.h"

int get_number(std::vector<int> const &digits, int start, int end)
{
    int n = 0;
    for (int i = start; i < end; i++)
        n = 10 * n + digits[i];
    return n;
}

std::vector<std::vector<int>> search(std::vector<int> const &digits, std::vector<int> const &slices)
{
    std::vector<std::vector<int>> results;

    if (slices.back() == 9)
    {
        results.emplace_back();
        std::vector<int> &numbers = results.back();
        for (int i = 0; i < slices.size() - 1; i++)
            numbers.emplace_back(get_number(digits, slices[i], slices[i + 1]));
        std::sort(numbers.begin(), numbers.end());
    }
    else
    {
        for (int index = slices.back() + 1; index < digits.size() + 1; index++)
        {
            if (util::is_prime(get_number(digits, slices.back(), index)))
            {
                std::vector<int> _slices(slices);
                _slices.emplace_back(index);
                std::vector<std::vector<int>> _results = search(digits, _slices);
                results.insert(results.end(), _results.begin(), _results.end());
            }
        }
    }

    return results;
}

int main()
{
    // We can't use std::unordered_set with constant insert time as std::vector<int>
    // has no hash defined.
    std::set<std::vector<int>> results;
    std::vector<int> digits(9);
    std::iota(digits.begin(), digits.end(), 1);
    do
    {
        std::vector<int> slices = { 0 };
        std::vector<std::vector<int>> _results = search(digits, slices);
        results.insert(_results.begin(), _results.end());
    } while (std::next_permutation(digits.begin(), digits.end()));

    std::cout << results.size();
}
