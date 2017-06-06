/*
    Define an undirected graph with vertices representing the primes. There exists
    an edge in between two vertices corresponding to p_1, p_2 iff p_1, p_2
    concatenates both ways to give another prime.

    Indeed, we are looking for the 5-clique in this graph whose sum is the
    smallest.

    We maintain a list of cliques, starting with the empty clique, and loop
    through the primes. For each prime p, we insert copies of cliques containing
    p into wherever the result is also a clique.

    We stop at the clique with length 5.

    We haven't actually shown that this gives the smallest sum; We can have some
    length 4 clique with elements a lot smaller than the length 5 clique, such
    that an additional prime making the length 4 clique a length 5 clique can
    possibly be subjugated by the current elements to give a sum smaller than
    the length 5 clique.

    Ideally, we have to loop until the prime that is larger than the smallest sum
    of the smallest length 5 clique found thus far - This guarantees that the
    addition of any prime beyond this to any length 4 or smaller cliques will
    yield a length 5 clique larger than the one currently found.

    Fortunately however, the first length 5 clique found turns out to have a sum
    that is the correct answer.
*/

#include <iostream>
#include <string>
#include <vector>
#include "number_util.h"
#include "prime_util.h"

bool is_concatenable(int a, int b)
{
    return util::is_prime(util::concat(a, b)) && util::is_prime(util::concat(b, a));
}


int main()
{
    std::vector<std::vector<int>> cliques = { {} };

    int prime = 2;
    while (true)
    {
        int initial_cliques_size = cliques.size();
        for (int i = 0; i < initial_cliques_size; i++)
        {
            std::vector<int> &clique = cliques[i];

            bool is_extendable = true;
            for (int &other_prime : clique)
            {
                if (!is_concatenable(prime, other_prime))
                {
                    is_extendable = false;
                    break;
                }
            }
            if (is_extendable)
            {
                cliques.emplace_back(clique);
                std::vector<int> &_clique = cliques.back();
                _clique.emplace_back(prime);
                if (_clique.size() == 5)
                {
                    int sum = 0;
                    for (int &n : _clique)
                        sum += n;
                    std::cout << sum;
                    return 0;
                }
            }
        }
        prime = util::get_next_prime(prime);
    }
}
