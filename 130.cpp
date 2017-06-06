/*
    We use the same A(n) algorithm as #129. Apart from that it is just naive
    search.
*/

#include <iostream>
#include "prime_util.h"

int A(int n)
{
    int residue = 1;
    int k = 1;
    while (residue != 0)
    {
        residue = (10 * residue + 1) % n;
        k++;
    }
    return k;
}

int main()
{
    int count = 0;
    int total = 0;
    int n = 2;
    while (count < 25)
    {
        if (n % 2 != 0 && n % 5 != 0)
        {
            if (!util::is_prime(n))
            {
                if ((n - 1) % A(n) == 0)
                {
                    count++;
                    total += n;
                }
            }
        }
        n++;
    }

    std::cout << total;
}
