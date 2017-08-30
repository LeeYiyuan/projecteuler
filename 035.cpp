/*
    Here, we use a set to store our primes instead of a vector becuse we are
    doing iteration, search and removal on the primes. To clarify, the
    "iteration" here refers to always picking out the smallest prime left. An
    unordered_set won't allow us to do this, while a sorted vector is slow when
    it comes to removal of elements. So we settle for a set.
*/

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "prime_util.h"

int main()
{
    std::vector<int> primes_vector = util::get_primes(1000000);
    std::set<int> primes(primes_vector.begin(), primes_vector.end());

    int count = 0;
    while (!primes.empty())
    {
        int prime = *primes.begin();
        primes.erase(primes.begin());

        std::string prime_string = std::to_string(prime);
        std::vector<int> rotations;

        for (int i = 0; i < prime_string.length() - 1; i++)
        {
            prime_string = prime_string[prime_string.length() - 1] + prime_string;
            prime_string.erase(prime_string.length() - 1);
            int _prime = std::stoi(prime_string);

            /*
              Below is to handle cases like 11, 1919. In such cases, equivalent
              rotations (i.e. equal permutations) will be considered twice during
              the subsequenct subset check which can lead to unexpected results.
            */
            if (_prime != prime && std::find(rotations.begin(), rotations.end(), _prime) == rotations.end())
                rotations.emplace_back(_prime);
        }

        bool rotation_are_primes = true;
        for (int &rotation : rotations)
        {
            auto it = primes.find(rotation);
            if (it != primes.end())
                primes.erase(it);
            else
                rotation_are_primes = false;
        }

        if (rotation_are_primes)
            count += 1 + rotations.size();
    }

    std::cout << count;
}
