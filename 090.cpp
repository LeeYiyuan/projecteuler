/*
    Let A and B be the arrangements of the two cubes respectively.

    For each n in 0, 1, ..., 9, we consider four cases:

        1: n is in both A and B.
        2: n is on only A.
        3: n is in only B.
        4: n is in neither A nor B.

    We get a decision tree with branching factor 4 and depth 10. It is not hard
    to brute force our way through since there are only 4^10 = 1048576 cases.
*/

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

typedef std::pair<std::vector<int>, std::vector<int>> case_type;
typedef std::pair<int, int> combination_type;

template <typename T>
bool contains(std::vector<T> const &v, T const &n)
{
    return std::find(v.begin(), v.end(), n) != v.end();
}

int main()
{
    std::vector<case_type> cases = {
        case_type()
    };
    std::vector<case_type> _cases;

    for (int n = 0; n < 10; n++)
    {
        std::vector<case_type> _cases;
        for (case_type &c: cases)
        {
            _cases.emplace_back(c);

            _cases.emplace_back(c);
            _cases.back().first.emplace_back(n);

            _cases.emplace_back(c);
            _cases.back().second.emplace_back(n);

            _cases.emplace_back(c);
            _cases.back().first.emplace_back(n);
            _cases.back().second.emplace_back(n);
        }
        cases = _cases;
    }

    for (case_type &c : cases)
        if (c.first.size() == 6 && c.second.size() == 6)
            _cases.emplace_back(c);
    cases = std::move(_cases);
    _cases = std::vector<case_type>();

    // We can't use unorderd_set because there is no default hash for pairs in C++17.
    std::set<combination_type> required_combinations({
        { 0, 1 },
        { 0, 4 },
        { 0, 9 },
        { 1, 6 },
        { 2, 5 },
        { 3, 6 },
        { 4, 9 },
        { 6, 4 },
        { 8, 1 },
    });

    // For each case, check if required set is a subset of possible combinations
    for (case_type &c : cases)
    {
        auto extended_case_A = c.first;
        if (contains(c.first, 6) && !contains(c.first, 9))
            extended_case_A.emplace_back(9);
        if (contains(c.first, 9) && !contains(c.first, 6))
            extended_case_A.emplace_back(6);
        auto extended_case_B = c.second;
        if (contains(c.second, 6) && !contains(c.second, 9))
            extended_case_B.emplace_back(9);
        if (contains(c.second, 9) && !contains(c.second, 6))
            extended_case_B.emplace_back(6);
        case_type extended_case(extended_case_A, extended_case_B);

        std::set<combination_type> combinations;
        for (int &a : extended_case.first)
        {
            for (int &b : extended_case.second)
            {
                combinations.emplace(a, b);
                combinations.emplace(b, a);
            }
        }

        if (std::includes(combinations.begin(), combinations.end(), required_combinations.begin(), required_combinations.end()))
            _cases.emplace_back(c);
    }
    cases = std::move(_cases);
    _cases = std::vector<case_type>();

    for (case_type &c : cases)
        if (!contains(_cases, case_type(c.second, c.first)))
            _cases.emplace_back(c);
    cases = std::move(_cases);
    _cases = std::vector<case_type>();

    std::cout << cases.size();
}
