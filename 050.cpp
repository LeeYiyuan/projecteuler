#include <iostream>
#include <vector>
#include <set>
#include "prime_util.h"

int get_longest_length(std::vector<int> const &primes, int i_p)
{
    int s = 0;
    int l = 0;
    int max_l = -1;
    while (s < 1000000 && i_p < primes.size())
    {
        s += primes[i_p];
        l++;
        if (std::binary_search(primes.begin(), primes.end(), s))
            max_l = l;
        i_p++;
    }
    return max_l;
}

int main()
{
    std::vector<int> primes = util::get_primes(999999);

    int value;
    int max_l = -1;
    for (int i_p = 0; i_p < primes.size(); i_p++)
    {
        int l = get_longest_length(primes, i_p);
        if (l > max_l)
        {
            value = 0;
            for (int j = 0; j < l; j++)
            {
                value += primes[i_p + j];
            }
            max_l = l;
        }
    }

    std::cout << value;
}
