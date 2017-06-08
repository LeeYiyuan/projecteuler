/*
    Again similar to #31 and #76.

    Let p(n, k) be the number of ways to partition n into parts that are at most
    k. Additionally, each part must be an element of C that contains the first
    primes up to k.

    Each partition must have a maximum value. This maximum value must be an
    element of C (because all parts are in C). We count each possible case to
    get:

        p(n, k) = \sum_{c in C | c <= min(n, k)} p(n - c, c)

    with p(0, k) = 1 for any k.

    We need the least value of n such that p(n, n) > 5000.

    Luckily unlike the previous #76 the recursion depth here is a low more
    shallow, so the program is still able to terminate quickly enough.
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include "prime_util.h"

int partitions(std::vector<int> &C, int n, int k)
{
    if (n == 0)
        return 1;
    while (C.back() < k)
        C.emplace_back(util::get_next_prime(C.back()));
    int sum = 0;
    for (int &c : C)
        if (c <= std::min(n, k))
            sum += partitions(C, n - c, c);
    return sum;
}

int main()
{
    int n = -1;
    std::vector<int> C = { 2 };
    while (partitions(C, ++n, n) <= 5000);

    std::cout << n;
}
