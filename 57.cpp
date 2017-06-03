/*
    Let a_n be the nth coefficient, where a_1 = 1 + 1/2. Then we have the
    recursive relation:

        a_{n + 1} = 1 + 1 / (1 + a_n)

    Suppose a_n is expressed as a fraction x_n / x_n where gcd(x_n, x_n) = 1.
    Then,

        a_{n + 1} = 1 + 1 / (1 + x_n / y_n)
        ...
        a_{n + 1} = (x_n + 2y_n) / (x_n + y_n)

    It turns out that since d | a, b => d | a - b, we have

        GCD(x_n + 2y_n, x_n + y_n)
        = GCD(y_n, x_n + y_n)
        = GCD(y_n, x_n)
        = 1

    and thus a_{n + 1} = (x_n + 2y_n) / (x_n + y_n) gives us the reduced
    fractional representation of a_{n + 1} given a_n = x_n / y_n.
*/

#include <iostream>
#include <gmpxx.h>

int main()
{
    int count = 0;
    mpz_class x = 1;
    mpz_class y = 1;
    for (int n = 0; n < 1000; n++)
    {
        mpz_class _x = x + 2 * y;
        mpz_class _y = x + y;
        x = _x;
        y = _y;

        if (x.get_str().length() > y.get_str().length())
            count++;
    }

    std::cout << count;
}
