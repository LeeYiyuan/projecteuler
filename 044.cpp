/*
    We start from p_b = p_2 and move towards the right.

    At each step we find the largest previous p_a such that p_b - p_a is a
    pentagonal number, and if p_b + p_a is a pentagonal number. If there is and
    the difference p_b - p_a is smaller than previous differences, output the
    difference.

    We loop until p_b - p_{b - 1} is greater than the smallest previously found
    difference, because for this b and beyond, the smallest difference of p_b -
    p_a for each b will always be greater than the previously found smallest
    difference.
*/

#include <cmath>
#include <iostream>
#include <climits>
#include <algorithm>

bool is_pentagonal(int p_n)
{
    double n = (1 + std::sqrt(1 + 24 * p_n)) / 6;
    return int(n) == n;
}

int get_pentagonal(int n)
{
    return n * (3 * n - 1) / 2;
}

int main()
{
    int min_diff = INT_MAX;

    int b = 2;
    int p_b = get_pentagonal(b);
    while (min_diff == INT_MAX or p_b - get_pentagonal(b - 1) > min_diff)
    {
        for (int a = 1; a < b; a++)
        {
            int p_a = get_pentagonal(a);
            if (is_pentagonal(p_b - p_a) && is_pentagonal(p_b + p_a))
                min_diff = std::min(min_diff, p_b - p_a);
        }
        b++;
        p_b = get_pentagonal(b);
    }

    std::cout << min_diff;
}
