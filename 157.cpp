#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include "number_util.h"
#include "prime_util.h"

typedef unsigned long long ull;

std::vector<ull> primes = { 2 };

std::vector<std::pair<ull, ull>> get_factors(int n)
{
    std::vector<std::pair<ull, ull>> pairs;

    // std::pow returns a double with mantissa 53 bits effective which I don't
    // think has enough precision for 10^{2n} <= 10^{18}.
    ull p = util::mpz_to<ull>(util::pow(10, 2 * n));

    for (ull e2 = 0, p2 = 1; e2 <= 2 * n; e2++, p2 *= 2)
        for (ull e5 = 0, p5 = 1; p2 * p5 <= p / (p2 * p5); e5++, p5 *= 5)
            pairs.emplace_back(p2 * p5, p / (p2 * p5));

    return pairs;
}

void get_solutions(int n, std::set<std::vector<ull>> &solutions)
{
    for (std::pair<ull, ull> &factor : get_factors(n))
    {
        ull f = util::mpz_to<ull>(util::pow(10, n)) + factor.first;
        ull g = util::mpz_to<ull>(util::pow(10, n)) + factor.second;
        ull d = util::gcd(f, g);
        ull step_a = f / d, step_b = g / d;

        ull k = 0;
        while ((++k) * k < d)
        {
            if (d % k == 0)
            {
                solutions.emplace(std::vector<ull>{ k * step_a, k * step_b, d / k, ull(n) });
                solutions.emplace(std::vector<ull>{ (d / k) * step_a, (d / k) * step_b, k, ull(n) });
            }
        }
        if (k * k == d)
        {
            solutions.emplace(std::vector<ull>{ k * step_a, k * step_b, k, ull(n) });
        }
    }
}

int main()
{
    std::set<std::vector<ull>> solutions;

    for (int n = 1; n <= 9; n++)
        get_solutions(n, solutions);

    std::cout << solutions.size();
}
