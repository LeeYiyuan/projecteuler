/*
    I actually got tricked into working hard and ended up wasting half a day
    when a such a naive solution works.

    :<
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <unordered_set>
#include "prime_util.h"
#include "number_util.h"

void search(
    int N,
    std::vector<int> const &primes,
    std::vector<std::vector<int>> const &powers,
    std::vector<int> const &solution,
    int sum_solution,
    int index,
    std::unordered_set<int> &results)
{
    if (solution.size() == powers.size())
    {
        results.emplace(sum_solution);
        return;
    }

    for (int const &power : powers[index])
    {
        if (sum_solution + power >= N)
            break;
        std::vector<int> _solution(solution);
        _solution.emplace_back(power);
        search(N, primes, powers, _solution, sum_solution + power, index + 1, results);
    }
}

int main()
{
    int N = 50000000;
    std::vector<int> primes = util::get_primes(int(std::sqrt(N)));
    std::vector<std::vector<int>> powers = { { }, { }, { } };

    for (int e = 2; e < 5; e++)
    {
        for (int &prime : primes)
        {
            int power = util::mpz_to<int>(util::pow(prime, e));
            if (power > N)
                break;
            powers[e - 2].emplace_back(power);
        }
    }

    std::unordered_set<int> results;
    std::vector<int> solution;
    search(N, primes, powers, solution, 0, 0, results);

    std::cout << results.size();
}
