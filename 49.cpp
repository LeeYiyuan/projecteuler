/*
    We loop through the primes and for each prime, we check if out of the 4!
    permutations, there are 3 that form an increasing sequence. If yes, then
    we have our solution. If not, we remove the 4! permutations from the list
    because they are permutations of one another and there is no need to check the
    cases for each other permutation again.
*/

#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <vector>
#include "prime_util.h"

int main()
{
    std::vector<int> primes_raw = get_primes(9999);
    std::set<int> primes;

    for (int &prime : primes_raw)
        if (prime >= 1000 && prime < 10000)
            primes.emplace(prime);

    while (!primes.empty())
    {
        int prime = *primes.begin();
        std::string prime_string = std::to_string(prime);

        std::vector<int> permutations;

        do
        {
            int permutation = std::stoi(prime_string);
            if (primes.find(permutation) != primes.end())
                if (std::find(permutations.begin(), permutations.end(), permutation) == permutations.end())
                    permutations.emplace_back(permutation);
        } while (std::next_permutation(prime_string.begin(), prime_string.end()));

        std::sort(permutations.begin(), permutations.end());

        for (int i_a = 0; i_a < permutations.size(); i_a++)
        {
            for (int i_b = i_a + 1; i_b < permutations.size(); i_b++)
            {
                for (int i_c = i_b + 1; i_c < permutations.size(); i_c++)
                {
                    int a = permutations[i_a], b = permutations[i_b], c = permutations[i_c];
                    if (b - a == c - b && a != 1487 && b != 4817 && c != 8147)
                    {
                        std::cout << std::to_string(a) << std::to_string(b) << std::to_string(c);
                        return 0;
                    }
                }
            }
        }

        for (int &permutation : permutations)
        {
            auto it = primes.find(permutation);
            if (it != primes.end())
                primes.erase(it);
        }
    }
}
