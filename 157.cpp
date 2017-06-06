#include <iostream>
#include <utility>
#include <vector>
#include "number_util.h"

typedef unsigned long long ull;

std::vector<std::pair<ull, ull>> get_factors(int n)
{
    std::vector<std::pair<ull, ull>> pairs;

    // std::pow returns a double with mantissa 53 bits effective which I don't
    // think has enough precision for 10^{2n} <= 10^{18}.
    ull p = mpz_to<ull>(pow(10, 2 * n));

    for (int e2 = 0, p2 = 1; e2 <= 2 * n; e2++, p2 *= 2)
        for (int e5 = 0, p5 = 1; p2 * p5 <= p / (p2 * p5); e5++, p5 *= 5)
            pairs.emplace_back(p2 * p5, p / (p2 * p5));

    return pairs;
}

std::vector<std::pair<ull, ull>> get_solutions(int n)
{
    std::vector<std::pair<ull, ull>> solutions;

    for (std::pair<ull, ull> &factor : get_factors(n))
    {
        ull f = mpz_to<ull>(pow(10, n)) + factor.first;
        ull g = mpz_to<ull>(pow(10, n)) + factor.second;
        ull d = gcd(f, g);
        ull step_a = f / d, step_b = g / d;

        ull a = 0, b = 0;
        while ((a += step_a) <= f && (b += step_b) <= g)
            if (f % a == 0 && g % b == 0)
                solutions.emplace_back(a, b);
    }

    return solutions;
}

int main()
{
    for (std::pair<ull, ull> &solution : get_solutions(6))
        std::cout << solution.first << " , " << solution.second << std::endl;
}
