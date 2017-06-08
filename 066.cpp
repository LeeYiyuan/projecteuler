/*
    To make life easier for future Pell equation realted problems, I've
    implemented a generalized Pell solver algorithm for x^2 - Dy^2 = N with D
    not a square based on a paper (refer to utils/pell_util.cpp).
*/

#include <iostream>
#include <gmpxx.h>
#include "pell_util.h"
#include "number_util.h"

int main()
{
    mpz_class x_max = 0;
    mpz_class D_max;

    for (int D = 2; D <= 1000; D++)
    {
        util::pell_solver solver(D, 1);
        if (solver.move_next())
        {
            mpz_class x = solver.solution.x;
            if (x > x_max)
            {
                x_max = x;
                D_max = D;
            }
        }
    }

    std::cout << D_max;
}
