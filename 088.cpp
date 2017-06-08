/*
    For all minimum product sums n of 2 <= k <= 12000, we guess that n <= 2 *
    12000.

    Next, for all integers n within this bound, we go through the possible
    factorizations of n containg terms larger than 1. Suppost we have a
    factorization with l terms. By appending j = product - sum number of 1s to
    the sum of these terms, we get a sum equal to the product, we can say that n
    is a (not necessarily minimal) product sum number for k = l + j.

    We collect product sum numbers n of k and for each k, pick the minimal one.
    Then, we sum up all distinct minimal product sum numbers across k.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>

int k_limit = 12000;

void search(int n, std::vector<int> &factorization, int product, std::unordered_map<int, int> &results)
{
    if (product == n)
    {
        int sum = std::accumulate(factorization.begin(), factorization.end(), 0);
        if (product >= sum)
        {
            int k = factorization.size() + product - sum;
            if (k >= 2 && k <= k_limit)
            if (results.find(k) == results.end())
                results[k] = n;
            else
                results[k] = std::min(results[k], n);
        }
        return;
    }

    for (int f = factorization.empty() ? 2 : factorization.back(); f <= n / product; f++)
    {
        if (n % f == 0)
        {
            std::vector<int> _factorization(factorization);
            _factorization.emplace_back(f);
            search(n, _factorization, product * f, results);
        }
    }
}

int main()
{
    std::unordered_map<int, int> results;
    for (int n = 2; n <= 2 * k_limit; n++)
    {
        std::vector<int> factorization;
        search(n, factorization, 1, results);
    }

    std::unordered_set<int> n_set;
    for (auto &result : results)
        n_set.emplace(result.second);

    std::cout << std::accumulate(n_set.begin(), n_set.end(), 0);
}
