#include <gmpxx.h>
#include <iostream>
#include "number_util.h"

int main()
{
    mpz_class product = factorial(mpz_class(100));

    int sum = 0;
    for (char &digit : product.get_str())
        sum += digit - '0';

    std::cout << sum;
}
