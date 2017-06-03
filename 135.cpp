/*
    First, we do some algebraic manipulations.

        n = x^2 - y^2 - z^2
          = x^2 - z^2 - y^2
          = (x + z)(x - z) - y^2
          = (2y)(2(x - y)) - y^2
          = 4xy - 5y^2
          = y(4x - 5y)

    We can search through valid pairs of (x, y) and add one to the counter for every
    corresponding n. Afterwards, we count the number of n whose counter reads 10.

    Now, we need to specify bounds for our iteration of (x, y). We will pick y first
    and then loop through x for every value of y. Since y | n, we need y <= n.

    For every y, we need n to be positive. We can start with x > 5y / 4, or
    x >= ceil(5y / 4). Since z must be positive and z = 2y - x, we have an upper bound
    x < 2y. Furthermore, for fixed y, n = y(4x - 5y) increases as x increases.
    This gives us the second upper bound that n = y(4x - 5y) <= n_max, which is 999999 in this case.
*/

#include <cmath>
#include <iostream>
#include <unordered_map>

int main()
{
    int n_max = 1000000;
    std::unordered_map<int, int> solution_counts;
    for (int y = 0; y < n_max; y++)
    {
        int x = std::ceil(y * 1.25);
        int n = y * (4 * x - 5 * y);
        while (n < n_max && x < 2 * y)
        {
            solution_counts[n]++;
            x++;
            n += 4 * y; // Because 4(x + 1)y - 5y^2 = (4xy - 5y^2) + 4y
        }
    }

    int count = 0;
    for (auto &pair : solution_counts)
        if (pair.second == 10)
            count++;

    std::cout << count;
}
