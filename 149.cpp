/*
    Essentially, for each of the 2000 rows, 2000 columns, 3999 diagonals and 3999
    anti diagonals, we have to look for the maximum subarray sum. Then, we pick
    the maximum of the maximum subarray sum across the 11998 cases.

    To look for the maximum subarray, we will use Kadane's algorithm which runs
    in O(n) time where n is the length of the input array.
*/

#include <iostream>
#include <vector>
#include <algorithm>

/*
    Kadane's algorithm, taken from https://en.wikipedia.org/wiki/Maximum_subarray_problem
    but modified to use iterators;
*/
int get_max_subarray_sum(std::vector<int> &A)
{
    auto it = A.begin();
    int max_ending_here;
    int max_so_far;
    max_ending_here = max_so_far = *it;
    while (++it != A.end())
    {
        max_ending_here = std::max(*it, max_ending_here + *it);
        max_so_far = std::max(max_so_far, max_ending_here);
    }
    return max_so_far;
}

int main()
{
    int l = 2000;

    std::vector<int> s;
    for (int k = 1; k <= 55; k++)
        s.emplace_back((100003 - 200003 * k + 300007 * (unsigned long long)(k) * k * k) % 1000000 - 500000);
    for (int k = 56; k <= 4000000; k++)
        s.emplace_back((*(s.end() - 24) + *(s.end() - 55) + 1000000) % 1000000 - 500000);

    std::vector<std::vector<int>> table(l, std::vector<int>(l));
    for (int r = 0; r < l; r++)
        for (int c = 0; c < l; c++)
            table[r][c] = s[l * r + c];

    int sum_max = -1;
    for (int i = 0; i < l; i++)
    {
        std::vector<int> A(table[i]);
        sum_max = std::max(sum_max, get_max_subarray_sum(A));

        A.clear();
        for (int r = 0; r < l; r++)
            A.emplace_back(table[r][i]);
        sum_max = std::max(sum_max, get_max_subarray_sum(A));

        A.clear();
        for (int j = 0; j <= i; j++)
            A.emplace_back(table[j][i - j]);
        sum_max = std::max(sum_max, get_max_subarray_sum(A));

        A.clear();
        for (int j = 0; j <= i; j++)
            A.emplace_back(table[l - 1 - j][i - j]);
        sum_max = std::max(sum_max, get_max_subarray_sum(A));

        A.clear();
        for (int j = 0; j <= i; j++)
            A.emplace_back(table[j][l - 1 - i + j]);
        sum_max = std::max(sum_max, get_max_subarray_sum(A));

        A.clear();
        for (int j = 0; j <= i; j++)
            A.emplace_back(table[l - 1 - j][l - 1 - i + j]);
        sum_max = std::max(sum_max, get_max_subarray_sum(A));
    }

    std::cout << sum_max;
}
