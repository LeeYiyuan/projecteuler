/*
    Let a_0, a_1, ..., a_99 be the 100 coefficients

        (1, 1, 2, 1, 1, 4, 1, ..., 1, 2k, 1, ...)

    required to determine the 100th convergent.

    Let b_n = a_{99 - n} + 1 / b_{n - 1} with b_0 = a_99.

    We enforce b_n as a fraction c_n / d_n. Then

        b_n = a_{99 - n} + d_{n - 1} / c_{n - 1}
        c_n / d_n = (a_{99 - n} * c_{n - 1} + d_{n - 1}) / c_{n - 1}

    so that

        c_n = a_{99 - n} * c_{n - 1} + d_{n - 1}
        d_n = c_{n - 1}

    Note that gcd(c_n, d_n) = gcd(d_{n - 1}, c_{n - 1}) = 1 so c_n / d_n is
    already reduced.

    We need to evaluate b_99.
*/

#include <iostream>
#include <vector>
#include <gmpxx.h>

int main()
{
    int target_convergent_number = 100;

    std::vector<int> a = { 2 };
    int k = 1;
    int i = 0;
    while (a.size() < target_convergent_number)
    {
        if (i % 3 == 0 || i % 3 == 2)
            a.emplace_back(1);
        else
            a.emplace_back(2 * k);
        i++;
        if (i >= 3) // Wrap around.
        {
            i = 0;
            k++;
        }
    }

    mpz_class c = a.back();
    mpz_class d = 1;

    for (int n = target_convergent_number - 2; n >= 0; n--)
    {
        mpz_class _c = c;
        c = a[n] * c + d;
        d = _c;
    }

    int sum = 0;
    do
    {
        mpz_class d = c % 10;
        sum += d.get_si();
    } while ((c /= 10) > 0);

    std::cout << sum;
}
