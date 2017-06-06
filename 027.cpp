#include <iostream>
#include "prime_util.h"

int main()
{
    int max_a;
    int max_b;
    int max_count = -1;

    for (int a = -999; a < 1000; a++)
    {
        for (int b = -1000; b <= 1000; b++)
        {
            int n = 0;
            while (util::is_prime(n * n + a * n + b))
                n++;
            if (n > max_count)
            {
                max_a = a;
                max_b = b;
                max_count = n;
            }
        }
    }

    std::cout << max_a * max_b;
}
