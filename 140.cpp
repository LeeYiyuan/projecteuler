/*
    We take the same approach as #137 but here we modify our solution to A(x)
    as the seed values are now different.

        A(x)         = G_1x + G_2x^2 + G_3x^3 + G_4x^4 + ...
        xA(x)        =        G_1x^2 + G_2x^3 + G_3x^4 + ...
        xA(x) + A(x) = G_1x + G_3x^2 + G_4x^3 + G_5x^4 + ...
                     = G_1x + (1/x)(A(x) - G_1x - G_2x^2)
        x^2A(x) + xA(x) = x^2 + A(x) - x - 4x^2
        x^2A(x) + xA(x) = A(x) - x - 3x^2
        (x^2 + x - 1)A(x) = -x - 3x^2
        A(x) = - (3x^2 + x) / (x^2 + x - 1)
             = (2x - 3) / (x^2 + x - 1) - 3

    Similar, we are interested in x such that A(x) = n for some positive integer
    n. That is,

        n + 3 = (2x - 3) / (x^2 + x - 1)
        (n + 3)x^2 + (n + 1)x - n = 0

    The discriminant must be a perfect square, i.e. for some positive integer m,

        (n + 1)^2 - 4(n + 3)(-n) = m^2
        n^2 + 2n + 1 + 4n^2 + 12n = m^2
        5n^2 + 14n + 1 = m^2
        25n^2 + 70n + 5 = 5m^2
        (5n + 7)^2 + 5 - 49 = 5m^2
        (5n + 7)^2 - 5m^2 = 44

    which is essentially the Pell equation a^2 - 5b^2 = 44 where (a, b) = (5n + 7, m).
    For every solution (a, b) we check if n is a positve integer. If it is, then
    x is rational and n is a golden nugget.
*/

#include <vector>
#include <iostream>
#include <gmpxx.h>
#include "pell_util.h"

int main()
{
    mpz_class sum_nugget = 0;
    int count = 0;
    pell_solver solver(5, 44);
    while (count < 30 && solver.move_next())
    {
        mpz_class a = solver.solution.x;
        mpz_class b = solver.solution.y;
        if (a > 7 && (a - 7) % 5 == 0)
        {
            mpz_class n = (a - 7) / 5;
            mpz_class m = b;
            sum_nugget += n;
            count++;
        }
    }

    std::cout << sum_nugget;
}
