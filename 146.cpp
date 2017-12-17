/*
    First, consider the residues of n^2 modulo primes p.

    For p = 2, we need n^2 to have a residue of 0, if not 2 | n^2 + 1. In this
    case we have n \equiv 0 \pmod 2.

    For p = 3, we need n^2 to have a residue other than 0 and 2, if not

        3 | n^2 + 3, n^2 + 9, n^2 + 27
        3 | n^2 + 1, n^2 + 7, n^2 + 13

    respectively. In this case we have n \equiv 1, 2 \pmod 3.

    For p = 5, we need n^2 to have a residue other than 1, 2, 3, 4, if not

        5 | n^2 + 9
        5 | n^2 + 3, n^2 + 13
        5 | n^2 + 7, n^2 + 27
        5 | n^2 + 1

    respectively. In this case, n \equiv 0 \pmod 5.

    We continue until p = 23. This is because in our subsequent application of
    the Chinese Remainder Theorem, we can determine the required residues of n
    modulo 2 * 3 * ... * 23, and 23 is the first prime p for which the primes up
    to and including p exceeds 150M.

    We can set up systems of linear congruence equations for each residue
    combinations across the prime modulus and for each combination, determine
    the required residue modulo 2 * 3 * ... * 23. For each solution n less than
    150M, we check if it satisfies the required conditions and list it as a hit
    if so.

    First, we see how we can solve a system of two linear equation,

        n \equiv a \pmod p
        n \equiv b \pmod q

    for (p, q) = 1. Let n = a + xp = b + yq. Then,

        a + xp = b + yq
        xp = (b - a) + yq
        xp \equiv b - a \pmod q
        x \equiv (b - a)p' \pmod q
          = d \pmod q

    where p' is the multiplicative inverse of p modulo q. We'll use the extended
    Euclidean Algorithm, like in #134, to find this inverse. Then,

        x = d + zq
        n = a + (d + zq)p
          = a + dp + zpq
          \equiv a + dp \pmod pq

    We can extend this solution of a two linear equation into a solution of a
    solution of a length n >= 2 system by eliminating equations one at a time.
    Notice that there is room for dynamic programming here.

    To check if n^2 + {1, 3, 7, 9, 13, 27} are consecutive primes, we only need
    to verify if n^2 + {1, 3, 7, 9, 13, 27} are primes, and n^2 + {15, 19, 21,
    25} are not primes. This is because all primes can be written in the form 6k
    \pm 1.

    There are various variations of this method. For example, instead of
    considering p = 2, 3, 5, ..., 23, we can consider simply p = 2, 3, 5, 7, in
    which case the density of necessary residues modulo 2 * 3 * 5 * 7 = 210 is
    very low - there are only 4 necessary residues. Then we loop through n as
    multiples of these residues less than 150M.

    This allows us to reduce the search space with respect to n by around 50
    times so that we only need search around 3M values of n. One can bring this
    futher by finding the optimal combination of prime modulus such that the
    density is minimized (if it is not already minimal at 2 * 3 * 5 * 7). These
    variations may or may not be faster than the solution here.

    I took some time to realize that this problem can be solved rather
    efficiently by simply considering non-residues modulo primes, and then using
    C.R.T.

    Initially I went to read up on twin primes and prime constellations, and
    primes of the form 6k \pm 1, which is where I got the idea for the
    consecutive primes check. Then I thought about quadratic residues which led
    to, after some simplifications, the current solution.

    Also I found out irrelevantly that there's such a thing called Euler's 6n +
    1 Theorem: It turns out that every prime of the form 6n + 1 can be written
    as x^2 + 3y^2 for some positive integers x, y. I had wanted to use this idea
    to generate possible n^2 + {3, 9}, because the larger of twin primes are
    always in the form 6k + 1, but realized this would be too slow. Nonethless
    this theorem is good to know :>.
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <gmpxx.h>
#include "prime_util.h"
#include "number_util.h"

std::pair<int, int> solve_congruence(int a, int p, int b, int q)
{
    int d = util::mod((b - a) * util::inv_mod(p, q), q);
    int n = util::mod(a + d * p, p * q);
    return { n, p * q };
}

int main()
{
    std::vector<int> offsets = { 1, 3, 7, 9, 13, 27 };
    std::vector<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
    std::vector<std::vector<int>> residues_list;

    for (int &prime : primes)
    {
        residues_list.emplace_back();
        std::vector<int> &residues = residues_list.back();
        for (int n = 0; n < prime; n++)
            if (std::all_of(offsets.begin(), offsets.end(), [&n, &prime](int &offset){ return ((n % prime) * (n % prime) + offset) % prime != 0; }))
                residues.emplace_back(n);
    }

    std::vector<std::pair<int, int>> congruences;
    for (int &residue : residues_list[0])
        congruences.emplace_back(residue, 2);

    for (int prime_index = 1; prime_index < primes.size(); prime_index++)
    {
        int prime = primes[prime_index];
        std::vector<std::pair<int, int>> _congruences;
        for (int &residue : residues_list[prime_index])
            for (std::pair<int, int> &congruence : congruences)
                _congruences.emplace_back(solve_congruence(congruence.first, congruence.second, residue, prime));
        congruences = _congruences;
    }

    std::vector<int> n_candidates;
    for (std::pair<int, int> &congruence : congruences)
    {
        int n = congruence.first;
        if (n < 150000000)
            n_candidates.emplace_back(n);
    }
    std::sort(n_candidates.begin(), n_candidates.end());

    int sum = 0;
    for (int &n : n_candidates)
    {
        mpz_class n2 = n;
        n2 *= n;
        if (!util::is_prime<mpz_class>(n2 + 15) && !util::is_prime<mpz_class>(n2 + 19) && !util::is_prime<mpz_class>(n2 + 21) && !util::is_prime<mpz_class>(n2 + 25) &&
            util::is_prime<mpz_class>(n2 + 1) && util::is_prime<mpz_class>(n2 + 3) && util::is_prime<mpz_class>(n2 + 7) && util::is_prime<mpz_class>(n2 + 9) &&
            util::is_prime<mpz_class>(n2 + 13) && util::is_prime<mpz_class>(n2 + 27))
        {
            sum += n;
        }
    }
    
    std::cout << sum;
}
