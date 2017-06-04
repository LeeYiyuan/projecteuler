/*
    This question here is very similar to #31. We have to find the number of
    partitions of 100 into sums of at least two positive integers.

    Let p(n, k) denote the number of ways to partition n into parts of at most k.

    Then the largest part of n can be 1, 2, ..., k. For each case, we count the
    number of partitions for the remainder of the n. This gives

         p(n, k) = p(n - 1, 1) + p(n - 2, 2) + ... p(n - k, k)

    with p(0, k) == 1.

    It turns out that the recursive form of this program takes too long. p(n, k)
    is calculated multiple times and time is wasted here to calculated the same
    value again and again.

    We turn this into a dynamic programming approach and calculate p(n, k) bottom
    up from n = 0 to 100, and for each n, from k = 0 to 100.
*/

#include <iostream>
#include <vector>
#include <algorithm>

int get_partitions(std::vector<std::vector<int>> &p, int n, int k)
{
    int sum = 0;
    for (int c = 1; c <= std::min(n, k); c++)
        sum += p[n - c][c];
    return sum;
}

int main()
{
    std::vector<std::vector<int>> p;

    // p(0, k) = 1
    p.emplace_back(101, 1);

    for (int n = 1; n <= 100; n++)
    {
        p.emplace_back(101); // p(1, k) to p(100, k)
        for (int k = 1; k < p.back().size(); k++)
            p.back()[k] = get_partitions(p, n, k);
    }

    std::cout << p[100][100] - 1;
}
