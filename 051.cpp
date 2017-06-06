#include <iostream>
#include <string>
#include <climits>
#include <algorithm>
#include "prime_util.h"

int main()
{
    int prime = 2;
    while (true)
    {
        int length = std::to_string(prime).length();

        for (int i = 0; i < (1 << length); i++)
        {
            int family_size = 0;
            int family_smallest = INT_MAX;
            int d = i >= (1 << (length - 1));
            for (; d < 10; d++)
            {
                int _prime = prime;
                int _i = i;
                int multiplier = 1;
                while (_i > 0)
                {
                    if (_i & 1)
                    {
                        _prime -= ((_prime / multiplier) % 10) * multiplier;
                        _prime += d * multiplier;
                    }
                    multiplier *= 10;
                    _i >>= 1;
                }
                if (util::is_prime(_prime))
                {
                    family_size++;
                    family_smallest = std::min(family_smallest, _prime);
                }
            }

            if (family_size == 8)
            {
                std::cout << family_smallest;
                return 0;
            }
        }

        prime = util::get_next_prime(prime);
    }
}
