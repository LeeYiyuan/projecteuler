/*
    Similar to #103, but we convert the generation of elements in A to a check of A.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include "io_util.h"
#include "string_util.h"

bool check(std::vector<int> &A)
{
    std::vector<std::vector<int>> subsets = {
        { },
        { A[0] },
        { A[1] },
        { A[0], A[1] }
    };

    for (int i = 2; i < A.size(); i++)
    {
        for (int l_check = 1; l_check < std::min(i, (int)A.size() - i + 1); l_check++)
            if (l_check * A[i] + l_check * (l_check - 1) / 2 > std::accumulate(A.begin(), A.begin() + l_check + 1, 0))
                return false;

        std::vector<std::vector<int>> _subsets;
        for (std::vector<int> &subset : subsets)
        {
            _subsets.emplace_back(subset);
            _subsets.back().emplace_back(A[i]);
        }

        for (std::vector<int> &_subset : _subsets)
        {
            int _subset_sum = std::accumulate(_subset.begin(), _subset.end(), 0);
            for (std::vector<int> &subset : subsets)
            {
                bool is_disjoint = true;
                for (const int &n : _subset)
                {
                    if (std::binary_search(subset.begin(), subset.end(), n))
                    {
                        is_disjoint = false;
                        break;
                    }
                }
                if (!is_disjoint)
                    continue;
                int subset_sum = std::accumulate(subset.begin(), subset.end(), 0);
                if (_subset_sum == subset_sum)
                    return false;
                if (_subset.size() < subset.size() && _subset_sum >= subset_sum)
                    return false;
                if (_subset.size() > subset.size() && _subset_sum <= subset_sum)
                    return false;
            }
        }

        subsets.insert(subsets.end(), _subsets.begin(), _subsets.end());
    }

    return true;
}

int main()
{
    std::string sets_string = util::read_file("105_sets.txt");
    std::vector<std::vector<int>> sets;
    for (std::string &row_string : util::split(sets_string, '\n'))
    {
        sets.emplace_back();
        std::vector<int> &set = sets.back();
        for (std::string &n_string : util::split(row_string, ','))
        {
            set.emplace_back(std::stoi(n_string));
        }
        std::sort(set.begin(), set.end());
    }

    int sum = 0;
    for (std::vector<int> &set : sets)
        if (check(set))
            sum += std::accumulate(set.begin(), set.end() , 0);

    std::cout << sum;
}
