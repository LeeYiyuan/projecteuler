/*
    Immediately we notice that A(x) is indeed the generating function for the
    Fibonacci numbers. The first thing we do, as usual, is to solve this generating
    function to get a closed form expression for A(x).

        A(x)         = F_1x + F_2x^2 + F_3x^3 + F_4x^4 + ...
        xA(x)        =        F_1x^2 + F_2x^3 + F_3x^4 + ...
        xA(x) + A(x) = F_1x + F_3x^2 + F_4x^3 + F_5x^4 + ...
                     = F_1x + (1/x)(A(x) - F_1x - F_2x^2)
        x^2A(x) + xA(x) = x^2 + A(x) - x - x^2
        x^2A(x) + xA(x) = A(x) - x
        (x^2 + x - 1)A(x) = -x
        A(x) = -x / (x^2 + x - 1)

    Now, we are interested in values of x for which A(x) = n for some positive
    integer n. That is,

        nx^2 + nx - n = -x
        nx^2 + (n + 1)x - n = 0

    In order for x to be rational, we can verify using the quadratic equation that
    the discriminant of the above quadratic must be a perfect square. That is for
    some non-negative integer m,

        (n + 1)^2 - 4(n)(-n) = m^2
        n^2 + 2n + 1 + 4n^2 = m^2
        5n^2 + 2n + 1 = m^2
        25n^2 + 10n + 5 = 5m^2
        (5n + 1)^2 + 4 = 5m^2
        (5n + 1)^2 - 5m^2 = -4

    Which gives us a Pell equation a^2 - 5b^2 = -4 where (a, b) = (5n + 1, m).
    For every solution (a, b) we check if n is a positive integer. If so, then
    n is a golden nugget as x is rational.
*/

#include <iostream>
#include <gmpxx.h>
#include "pell_util.h"

int main()
{
    int count = 0;
    mpz_class n;
    util::pell_solver solver(5, -4);
    while (count < 15 && solver.move_next())
    {
        mpz_class a = solver.solution.x;
        mpz_class b = solver.solution.y;
        if ((a - 1) % 5 == 0)
        {
            mpz_class _n = (a - 1) / 5;
            mpz_class m = b;
            if (_n > 0)
            {
                count++;
                n = _n;
            }
        }
    }

    std::cout << n;
}
