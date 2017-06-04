#include <gmpxx.h>
#include <iostream>
#include "number_util.h"

int main()
{
    mpz_class m = 10000000000;

    std::cout << (28433 * pow_mod(2, 7830457, m) + 1) % m;
}
