/*
    Firstly, we calculate rad(n) for n = 1, ..., 120000 - 1 efficiently by
    considering multiples of primes < 1200000 - 1, just like we did in #124.
    This gives us a table mapping n -> rad(n).

    Secondly, note that since gcd(a, b) = gcd(a, c) = gcd(b, c) = 1, the prime
    factors of each a, b, c are unique and do not overlap. As such, we have

        rad(abc) = rad(a)rad(b)rad(c)

    Since we need rad(abc) < c, we can pick c such that rad(c) < c. These are
    all non-square free numbers c. If c is square free, rad(c) = c and since
    rad(abc) >= rad(c), there will be no candidates for a, b.

    Now, we design a nested loop across c and b. For each (c, rad(c)) such that
    rad(c) < c, we pick (b, rad(b)) such that rad(b)rad(c) < c. At this point it
    is useful to sort (n, rad(n)) according to rad(n) so we can limit the inner
    loop to (b, rad(b)) such that rad(b)rad(c) < c.

    For selected (b, rad(b)) and (c, rad(c)), we can deduce a = c - b from the
    conditions imposed. Then, we check if a > 0 and a < b. If it does, we check
    if gcd(b, c) = 1. Notice that gcd(b, c) = 1 is enough to prove gcd(a, b) =
    gcd(a, c) = gcd(b, c) = 1, because a = c - b and

        gcd(a, b) = gcd(c - b, b) = gcd(c, b) = 1
        gcd(a, c) = gcd(c - b, c) = gcd(c - b, b) = gcd(c, b) = 1

    Finally, we check the remaining condition - If rad(a)rad(b)rad(c) < c. If this
    is met, we add c to our sum of c.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include "prime_util.h"
#include "number_util.h"

int main()
{
    int c_max = 120000;

    std::vector<int> primes = util::get_primes(c_max - 1);
    std::vector<int> n_to_rad(c_max, 1);
    for (int &p : primes)
    {
        int q = 0;
        while ((++q) * p < c_max)
            n_to_rad[q * p] *= p;
    }

    std::vector<std::pair<int, int>> rad;
    for (int n = 1; n < c_max; n++)
        rad.emplace_back(n, n_to_rad[n]);
    std::sort(rad.begin(), rad.end(), [](std::pair<int, int> &a, std::pair<int, int> &b)
    {
        return a.second < b.second;
    });

    int sum = 0;
    for (std::pair<int, int> &c_rad_c : rad)
    {
        int c = c_rad_c.first; int rad_c = c_rad_c.second;
        if (rad_c < c)
        {
            for (std::pair<int, int> &b_rad_b : rad)
            {
                int b = b_rad_b.first; int rad_b = b_rad_b.second;
                if (rad_b * rad_c >= c)
                    break;

                int a = c - b;
                if (a > 0 && a < b)
                {
                    int rad_a = n_to_rad[a];
                    if (util::gcd(b, c) == 1 && (uint64_t)(rad_a) * rad_b * rad_c < c)
                        sum += c;
                }
            }
        }
    }

    std::cout << sum;
}
