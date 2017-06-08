/*
    Let p_1, p_2, ..., p_k be the prime factors of n. Then Euler's product
    formula says that

        n / \phi(n) = n / (n(1 - 1/p_1)(1 - 1/p_2)...(1 - 1/p_k))
                    = \product_{i = 1}^k p_i / (p_i - 1)

    Each of these products are more than 1 and also

        p_a / (p_a - 1) > p_b / (p_b - 1)

    whenever a < b. So intuitively, we want as many prime factors that are as
    small as possible.

    We come to a conjecture guess that the maximum of n / \phi(n) occurs at the
    product of the first k primes, where k is smallest integer such that the
    product of the first k + 1 primes exceeds 1000000.

    Fortunately, this leads to the accepted answer.
*/

#include <iostream>
#include <vector>
#include "prime_util.h"

int main()
{
    std::vector<int> primes = { 2 };
    int product = 1;
    while (product * primes.back() <= 1000000)
    {
        product *= primes.back();
        primes.emplace_back(util::get_next_prime(primes.back()));
    }

    std::cout << product;
}
