/*
    Consider a pair of subsets (A, B) with lengths n_A and n_B respectively.
    If n_A != n_B then either n_A > n_B or n_A < n_B and therefore S(A) > S(B)
    and S(A) < S(B) respectively; That is, we only need to check pairs of subsets
    with equal length for the first condition.

    To prevent double counting, we pick pairs of disjoint subsets (A, B) with equal
    lengths such that the smallest element of A is smaller than the smallest element
    of B.

    Notice that starting from the first element, we can "cancel" the smallest element
    of A from the smallest element of B. If we are able to cancel all elements, then
    it is implied that S(A) < S(B) and thus (A, B) need not be checked.

    On the other hand, if we reach an index where cancellation can't work (i.e. the
    element of A at that index is larger than the element of B at that index), then
    we know that there is a need to check this pair as it is not guaranteed that
    S(A) < S(B).
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include "iter_util.h"

int main()
{
    std::vector<int> numbers(12);
    std::iota(numbers.begin(), numbers.end(), 0);

    int count = 0;
    for (int _n = 2; _n <= numbers.size() / 2; _n++)
    {
        for (std::vector<int> &_a : util::get_combinations(numbers.begin(), numbers.end(), _n))
        {
            std::vector<int> _b_numbers;
            for (int &e : numbers)
                if (!std::binary_search(_a.begin(), _a.end(), e))
                    _b_numbers.emplace_back(e);
            for (std::vector<int> &_b : util::get_combinations(_b_numbers.begin(), _b_numbers.end(), _n))
            {
                if (_a > _b)
                    continue;

                int n = _n;
                std::vector<int> a(_a), b(_b);
                while (n > 0 && a[0] < b[0])
                {
                    a.erase(a.begin());
                    b.erase(b.begin());
                    n--;
                }
                if (n > 0)
                    count++;
            }
        }
    }

    std::cout << count;
}
