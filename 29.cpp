#include <iostream>
#include <vector>
#include <prime_util.h>

int main()
{
    std::vector<int> primes = get_primes(100);

    std::vector<std::vector<int>> factorizations;

    for (int i = 2; i <= 100; i++)
    {
        int _i = i;
        factorizations.emplace_back(primes.size());
        std::vector<int> &factorization = factorizations.back();
        for (int prime_index = 0; prime_index < primes.size(); prime_index++)
        {
            int prime = primes[prime_index];
            while (_i % prime == 0)
            {
                factorization[prime_index]++;
                _i /= prime;
            }
        }
    }

    std::vector<std::vector<int>> terms;
    for (std::vector<int> a_factorization : factorizations)
    {
        for (int b = 2; b <= 100; b++)
        {
            std::vector<int> term(a_factorization.size());
            for (int i = 0; i < a_factorization.size(); i++)
                term[i] = a_factorization[i] * b;
            if (std::find(terms.begin(), terms.end(), term) == terms.end())
                terms.emplace_back(term);
        }
    }

    std::cout << terms.size();
}
