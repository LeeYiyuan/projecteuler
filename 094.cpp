/*
    Consider triangles with sides a, a, b where b = a \pm 1. Let the altitude of
    this triangle with base b be c. Then,

        a^2 = c^2 + b^2 / 4
        4a^2 = 4c^2 + (a + 1)^2 , 4c^2 + (a - 1)^2
        4a^2 = 4c^2 + a^2 + 2a + 1, 4c^2 + a^2 - 2a + 1
        3a^2 - 2a - 4c^2 = 1, 3a^2 + 2a - 4c^2 = 1
        9a^2 - 6a - 12c^2 = 1, 9a^2 + 6a - 12c^2 = 1
        (3a - 1)^2 - 1 - 12c^2 = 3, (3a + 1)^2 - 1 - 12c^2 = 3
        (3a - 1)^2 - 3(2c)^2 = 4, (3a + 1)^2 - 3(2c)^2 = 4

    So we essentially have to solve the Pell equation x^2 - 3y^2 = 4.
*/

#include <iostream>
#include <gmpxx.h>
#include "pell_util.h"

int main()
{
    mpz_class p_max = 1000000000;
    mpz_class sum = 0;
    util::pell_solver solver(3, 4);

    while (solver.move_next())
    {
        mpz_class _a = solver.solution.x;
        mpz_class _b = solver.solution.y;
        mpz_class a, b;

        if ((_a + 1) % 3 == 0) // b = a - 1.
        {
            a = (_a + 1) / 3;
            b = a - 1;
        }
        else if ((_a - 1) % 3 == 0) // b = a + 1.
        {
            a = (_a - 1) / 3;
            b = a + 1;
        }

        if (2 * a + b > p_max)
            break;

        if (2 * a > b)
            sum += 2 * a + b;
    }

    std::cout << sum;
}
