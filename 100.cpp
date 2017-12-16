/*
    In general, suppose there are b blue discs and r red discs. Then the
    probability of taking two blue discs at random is

        P(BB) = (b / (b + r)) x ((b - 1) / (b + 1 - r))

    We need (b, r) such that P(BB) = 1 / 2. That is,

        2b(b - 1) = (b + r)(b + r - 1)
        2b^2 - 2b = b^2 + 2br + r^2 - b - r
        b^2 - b - 2br - r^2 + r = 0
        b^2 + (-1 - 2r) b + (-r^2 + r) = 0

    By considering the quadratic formula for the above equation in b, every
    integer b requires a discriminant that is a perfect square. That is, for
    every positive integer solution (c, r) to the Pell equation

        (-1 - 2r)^2 - 4(1)(-r^2 + r) = c^2
        4r^2 + 4r + 1 + 4r^2 - 4r = c^2
        c^2 - 8r^2 = 1

    where c, r are positive integers, we need to check if

        b = (1 + 2r + c) / 2

    is a positive integer. Note that c^2 = 1 + 8r^2 > 4r^2, so c > 2r and thus
    we can ignore the case of the quadratic equation where we consider -c
    instead of +c.
*/

#include <iostream>
#include <gmpxx.h>
#include "pell_util.h"
#include "number_util.h"

int main()
{
    mpz_class limit = util::pow(mpz_class(10), 12);
    util::pell_solver solver(8, 1);
    while (solver.move_next())
    {
        mpz_class c = solver.solution.x;
        mpz_class r = solver.solution.y;

        mpz_class b = 1 + 2 * r + c;
        if (b % 2 != 0)
            continue;
        b /= 2;
        if (b + r > limit)
        {
            std::cout << b;
            return 0;
        }
    }
}
