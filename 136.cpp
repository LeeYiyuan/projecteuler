/*
    Similar to #135.

    Here we use a bitset instead of an unordered_set because we need not track
    count but only check for duplicates. A bitset uses less memory for
    representing sparse bit arrays, and is faster than an unordered_set because
    key-value pairs need not be created on the fly.
*/

#include <iostream>
#include <bitset>

int main()
{
    int const n_max = 50000000;

     // Allocate on heap to prevent segfault from insufficient stack space.
    std::bitset<n_max> *unique = new std::bitset<n_max>();
    std::bitset<n_max> *duplicate = new std::bitset<n_max>();

    for (int y = 0; y < n_max; y++)
    {
        int x = y * 5 / 4 + 1;
        int n = y * (4 * x - 5 * y);
        while (n < n_max && x < 2 * y)
        {
            //std::cout << n << std::endl << std::flush;
            if ((*unique)[n])
            {
                (*unique)[n] = false;
                (*duplicate)[n] = true;
            }
            else if (!(*duplicate)[n])
            {
                (*unique)[n] = true;
            }

            x++;
            n += 4 * y; // Because 4(x + 1)y - 5y^2 = (4xy - 5y^2) + 4y
        }
    }

    std::cout << unique->count();

    delete unique, duplicate;
}
