#include <iostream>
#include <gmpxx.h>
#include "number_util.h"

int main()
{
    mpz_class n = pow(2, 1000);

    int s = 0;
    for (char &digit : n.get_str())
        s += digit - '0';

    std::cout << s;
}
