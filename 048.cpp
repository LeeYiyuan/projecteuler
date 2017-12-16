/*
    Modular exponetiation by squaring.
*/

#include <iostream>
#include <gmpxx.h>
#include "number_util.h"

int main()
{
    mpz_class modulo("10000000000");
    mpz_class remainder = 0;

    for (int i = 1; i <= 1000; i++)
        remainder = (remainder + util::pow_mod(mpz_class(i), i, modulo)) % modulo;

    std::cout << remainder;
}
