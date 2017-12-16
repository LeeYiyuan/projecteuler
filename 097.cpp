#include <gmpxx.h>
#include <iostream>
#include "number_util.h"

int main()
{
    mpz_class m = 10000000000;

    std::cout << (28433 * util::pow_mod(mpz_class(2), 7830457, m) + 1) % m;
}
