/*
    By using multinomial expansion, the coefficients of (x + y + z)^200000
    are given by 200000!/(i!j!k!) where i + j + k = 200000.

    We exploit symmetry to reduce the search space over i, j, k. We assume W.L.O.G
    that i <= j <= k. We search over i starting from i = 0, and for every i we
    search over j starting with j = i while k = s - i - j is at least j.

    For every (i, j, k) we check if p2(i) + p2(j) + p2(k) <= p2(s) - 12 and
    p5(i) + p5(j) + p5(k) <= p5(s) - 12, where s = 200000, p2(n) gives the
    largest exponent of 2 dividing n, and p5(n) gives the largest exponent of 5
    dividing n. A table for p2(n) and p5(n) is first generated to cache computations.

    If (i, j, k) satisfies the required conditions, we check the equality of
    i, j, k. If none are equal, then we have 6 permutations for i, j, k without
    the constraint that i <= j <= k. If one pair is equal, i.e. i == j or j == k,
    then there are 3 permutations. If all three are equal, there is only one
    permutation.

    We sum up the permutations over our search space to give the result.
*/

#include <iostream>
#include <vector>

int main()
{
    int s = 200000;

    std::vector<int> ntop2(s + 1);
    std::vector<int> ntop5(s + 1);
    int p2 = 0;
    int p5 = 0;
    for (int n = 0; n <= s + 1; n++)
    {
        if (n > 0)
        {
            int _n = n;
            while (_n % 2 == 0)
            {
                p2++;
                _n /= 2;
            }
            _n = n;
            while (_n % 5 == 0)
            {
                p5++;
                _n /= 5;
            }
        }
        ntop2[n] = p2;
        ntop5[n] = p5;
    }

    long long count = 0;
    int i = 0;
    while (3 * i <= s)
    {
        int j = i;
        int k = s - i - j;
        while (k >= j)
        {
            if (ntop2[i] + ntop2[j] + ntop2[k] <= ntop2[s] - 12 &&
                ntop5[i] + ntop5[j] + ntop5[k] <= ntop5[s] - 12)
            {
                if (i == j && j == k)
                    count++;
                else if (i == j && j < k)
                    count += 3;
                else if (i < j && j == k)
                    count += 3;
                else if (i < j && j < k)
                    count += 6;
            }
            j++;
            k--;
        }
        i++;
    }

    std::cout << count;
}
