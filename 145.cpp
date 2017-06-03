/*
    We consider reversible numbers n with l digits where l = 2, 3, ..., 9, and
    let the digits of n be

        a_0,    a_1,        ...,    a_{l - 1},  a_l

    The reverse of n is then

        a_l,    a_{l - 1},  ...,    a_1,        a_0

    Instead of enumerating all possible a_0, a_1, ..., a_l, we only need
    to enumerate the possible valid sums a_0 + a_1, a_1 + a_{l - 1} + ..., which
    we can do using breadth first expansion. For each digit sum a_i + a_{k - i - 1}
    we can count directly the number of cases.

    Of course, there are some exceptions we must account for.

    Firstly, the number of cases for the first and last digits differ from the
    other digits, because the first and last digits cannot be zero while the others
    can.

    Secondly, if the length is odd, then the central sum a_{l / 2} + a{l / 2} must
    be even, because it is the sum of the same two numbers. Furthermore, there will
    for a_{l / 2} + a{l / 2} there will only be one case per sum.
*/

#include <vector>
#include <iostream>
#include <algorithm>

std::vector<int> initial_digit_cases = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 8, 7, 6, 5, 4, 3, 2, 1 };
std::vector<int> digit_cases = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

std::vector<std::vector<int>> get_digit_sums_list(int length)
{
    std::vector<std::vector<int>> digit_sums_list = {
        { 0, 3 },
        { 0, 5 },
        { 0, 7 },
        { 0, 9 },
        { 1, 11 },
        { 1, 13 },
        { 1, 15 },
        { 1, 17 }
    };

    for (int i = 1; i < length; i++)
    {
        std::vector<std::vector<int>> _digit_sums_list;
        for (std::vector<int> &digit_sums : digit_sums_list)
        {
            int carry = digit_sums[0];
            for (int i = 0; i < 19; i++)
            {
                if ((i + carry) % 2 == 1)
                {
                    _digit_sums_list.emplace_back(digit_sums);
                    _digit_sums_list.back().emplace_back(i);
                    _digit_sums_list.back()[0] = (i + carry) / 10;
                }
            }
        }
        digit_sums_list = _digit_sums_list;
    }

    // Remove carry digits.
    for (std::vector<int> &digit_sums : digit_sums_list)
        digit_sums.erase(digit_sums.begin());

    return digit_sums_list;
}

int count_cases(int l)
{
    bool is_odd = l % 2 == 1;
    int k = is_odd ? (l + 1) / 2 : l / 2;

    std::vector<std::vector<int>> digit_sums_list = get_digit_sums_list(k);
    if (is_odd)
    {
        std::vector<std::vector<int>> _digit_sums_list;
        for (std::vector<int> &digit_sums : digit_sums_list)
            if (digit_sums.back() % 2 == 0)
                _digit_sums_list.emplace_back(digit_sums);
        digit_sums_list = _digit_sums_list;
    }

    int total_cases_count = 0;
    for (std::vector<int> &digit_sums : digit_sums_list)
    {
        std::vector<int> next_digit_sums = is_odd ?
            std::vector<int>(digit_sums.begin(), digit_sums.end() - 1) :
            std::vector<int>(digit_sums);
        std::reverse(next_digit_sums.begin(), next_digit_sums.end());

        std::vector<int> combined_digit_sums(digit_sums);
        combined_digit_sums.insert(combined_digit_sums.end(), next_digit_sums.begin(), next_digit_sums.end());
        int carry = 0;
        std::vector<int> digits;
        for (int &digit_sum : combined_digit_sums)
        {
            digits.emplace_back((digit_sum + carry) % 10);
            carry = (digit_sum + carry) / 10;
        }
        if (carry > 0)
            digits.emplace_back(carry);

        if (std::count_if(digits.begin(), digits.end(), [](int &digit){ return digit % 2 == 0; }) > 0)
            continue;

        int cases_count = initial_digit_cases[digit_sums[0]];
        for (int i = 1; i < (is_odd ? (digit_sums.size() - 1) : digit_sums.size()); i++)
            cases_count *= digit_cases[digit_sums[i]];

        total_cases_count += cases_count;
    }

    return total_cases_count;
}

int main()
{
    int count = 0;
    for (int l = 2; l < 10; l++)
        count += count_cases(l);

    std::cout << count;
}
