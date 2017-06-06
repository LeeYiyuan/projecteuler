/*
    Initially I came up with some formulas that allow, given (a, b, c), one to find
    p + q + r by using areas of triangles, the fact that all angles on T are
    120 degrees, and the factorization p^2 + q^2 + r^2 = (p + q + r)^2 - 2(pq + qr + rp).
    However checking across (a, b, c) to see if p + q + r is an integer, which is
    necessary for p, q, r to be integers, was too slow. So I tried to simplify things a
    bit.

    By considering the cyclic quadilateral TCBN one can show that angle CTB = 120
    as angle CTB + angle CNB = 180 and angle CNB = 60. In general, all angles at T
    are exactly 120.

    By the cosine formula, we can deduce that

        a^2 = q^2 + r^2 + qr
        b^2 = p^2 + q^2 + pq
        c^2 = r^2 + p^2 + rp

    so we need to look for integers (p, q, r) such that (a, b, c) are integers as well.

    One can attempt to brute force his way through (p, q, r) but this is too slow.
    Hence we try to look for some parametrization, like Euclid's formula for Pythagorean
    triples, that can generate integers (f, g, h) such that h^2 = f^2 + g^2 + fg.

    Unfortunately I could not come up with a parameterization myself. So I relied on the
    parameterization from http://www.geocities.ws/fredlb37/node9.html, namely:

        f = k(m^2 - n^2)
        g = k(2mn + n^2)
        h = k(m^2 + n^2 + mn)

    where gcd(m, n) = 1, m > n, 3 does not divide m - n, and k is some positive integer.

    Now, to search for (p, q, r). First we collect valid (f, g) using the parametrization
    described above into a list I shall name list_fg. For each (f, g), we swap f and g
    if g < f, so that f <= g eventually.

    Assume without loss of generality that p <= q <= r. We loop through (f, g) in list_fg
    and for each (f, g), we assign (p, q) = (f, g). Then we take all (f', g')
    immediately after (f, g) such that f' = p, and assign r = g'. Since (f', g') comes
    after (f, g) and f = f', we can be sure that g' >= g and therefore r >= q. If
    (q, r) is in list_fg then we have a hit (p, q, r).

    We keep list_fg sorted so that we can use binary search to optimize checking
    if (q, r) is in list_fg.
*/

#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <numeric>
#include "number_util.h"

int main()
{
    int limit = 120000;
    std::vector<std::pair<int, int>> list_fg;

    int n = 1;
    while (2 * 1 * n + n * n <= limit)
    {
        int m = n + 1;
        while (2 * m * n + n * n <= limit)
        {
            if (util::gcd(m, n) == 1 && (m - n) % 3 != 0)
            {
                int f = m * m - n * n;
                int g = 2 * m * n + n * n;
                int h = m * m + n * n + m * n;
                if (g < f)
                    std::swap(g, f);
                int k = 1;
                while (k * f + k * g <= limit)
                {
                    list_fg.emplace_back(k * f, k * g);
                    k++;
                }
            }
            m++;
        }
        n++;
    }
    std::sort(list_fg.begin(), list_fg.end());

    std::set<int> sums;
    for (auto it_fg = list_fg.begin(); it_fg != list_fg.end(); ++it_fg)
    {
        for (int offset = 1; (it_fg + offset) != list_fg.end() && (it_fg + offset)->first == it_fg->first; offset++)
        {
            int r = (it_fg + offset)->second;
            if (std::binary_search(list_fg.begin(), list_fg.end(), std::pair<int, int>(it_fg->second, r)))
            {
                int s = it_fg->first + it_fg->second + r;
                if (s <= limit)
                    sums.emplace(s);
            }
        }
    }

    std::cout << std::accumulate(sums.begin(), sums.end(), 0);
}
