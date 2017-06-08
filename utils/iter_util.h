#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

namespace util
{
    template <typename InputIterator>
    std::vector<std::vector<InputIterator>> get_combinations_it(InputIterator first, InputIterator last, int r)
    {
        std::vector<std::vector<InputIterator>> combinations_it;

        int n = std::distance(first, last);
        std::vector<bool> flags(n);
        std::iota(flags.end() - r, flags.end(), true);
        do
        {
            combinations_it.emplace_back();
            for (int i = 0; i < flags.size(); i++)
                if (flags[flags.size() - 1 - i])
                    combinations_it.back().emplace_back(first + i);
        } while (std::next_permutation(flags.begin(), flags.end()));

        return combinations_it;
    }

    template <typename InputIterator>
    std::vector<std::vector<typename InputIterator::value_type>> get_combinations(InputIterator first, InputIterator last, int r)
    {
        std::vector<std::vector<typename InputIterator::value_type>> combinations;
        for (std::vector<InputIterator> &combination_it : util::get_combinations_it(first, last, r))
        {
            combinations.emplace_back();
            for (InputIterator &it : combination_it)
                combinations.back().emplace_back(*it);
        }

        return combinations;
    }
}
