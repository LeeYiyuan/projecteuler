#include <iostream>
#include <vector>
#include <algorithm>
#include "number_util.h"

bool cancel(int &n, int &d)
{
    int n0 = n / 10, n1 = n % 10;
    int d0 = d / 10, d1 = d % 10;

    if (n0 == d0){ n0 = -1; d0 = -1; }
    else if (n0 == d1){ n0 = -1; d1 = -1; }

    if (n1 == d0){ n1 = -1; d0 = -1;}
    else if (n1 == d1){ n1 = -1; d1 = -1; }

    if (n0 == -1 and n1 == -1) n = 0;
    else if (n0 == -1) n = n1;
    else if (n1 == -1) n = n0;
    else return false;

    if (d0 == -1 and d1 == -1) d = 0;
    else if (d0 == -1) d = d1;
    else if (d1 == -1) d = d0;
    else return false;

    return true;
}

int main()
{
    int n_product = 1, d_product = 1;
    for (int n = 10; n < 100; n++)
    {
        for (int d = n + 1; d < 100; d++)
        {
            int _n = n, _d = d;
            // n/d = _n/_d <=> n*_d = d*_n
            if (cancel(_n, _d) && _d != 0 && n * _d == d * _n && n % 10 != 0 && d % 10 != 0)
            {
                n_product *= n;
                d_product *= d;
            }
        }
    }

    int g = gcd(n_product, d_product);

    std::cout << d_product / g;
}
