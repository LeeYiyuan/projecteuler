/*
    We use dynamic programming to keep track of how many l digit increasing
    and decreasing numbers there are separately. Specifically, we store the number
    of l digit increasing numbers that start with a certain digit 0 - 9.

    For a l digit increasing number that starts with digit d, we know that the next
    digit must be a l - 1 digit number that starts with one of d, d + 1, ..., 9.
    We add these up to give the number of l digit increasing numbers starting with
    digit d, and repeat if for every d = 0, ..., 9.

    After doing this for 100 digits, we sum up the number of l digit increasing
    numbers starting with digit d for l = 1, 2, ..., 100 and d = 1, ..., 9. We
    extend our argument and get another sum for decreasing numbers.

    The increasing numbers and decreasing numbers overlap in cases where all digits
    are the same, for example 11111, 99, 3333. For each number length l there
    are 9 such cases, and thus for l = 1, ..., 100, there are a total of 999 cases.

    By the Inclusion-Exclusion Principle, the number of non bouncy numbers, which is
    the number of increasing or decreasing numbers, is the sum of the number of
    increasing with the number of decreasing numbers, minus the overlapping count.
*/

#include <iostream>
#include <vector>

typedef unsigned long long ull;

int main()
{
    std::vector<std::vector<ull>> increasing_counts = {
        { },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };
    std::vector<std::vector<ull>> decreasing_counts = {
        { },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };

    int n_digits = 100;
    for (int l = 2; l <= n_digits; l++)
    {
        increasing_counts.emplace_back();
        decreasing_counts.emplace_back();
        for (int d = 0; d < 10; d++)
        {
            increasing_counts.back().emplace_back(0);
            for (int _d = d; _d < 10; _d++)
                increasing_counts.back().back() += increasing_counts[l - 1][_d];
            decreasing_counts.back().emplace_back(0);
            for (int _d = 0; _d <= d; _d++)
                decreasing_counts.back().back() += decreasing_counts[l - 1][_d];
        }
    }

    ull non_bouncy_count = 0;
    for (int l = 1; l <= n_digits; l++)
        for (int d = 1; d < 10; d++)
            non_bouncy_count += increasing_counts[l][d] + decreasing_counts[l][d];

    non_bouncy_count -= 9 * n_digits;

    std::cout << non_bouncy_count;
}
