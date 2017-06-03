/*
    Suppose a number n can be written as the sum of fifth powers of its digits.
    Then the number n is at most

        n <= (\floor\lg{n} + 1) * 9^5
        n / (\floor\lg{n} + 1) <= 9^5

    Contrapositively, n that does not satisfy this requirement cannot be written
    as the sum of fifth powers of its digits.

    Since LHS is strictly increasing, we only need to loop while n satisfies
    the above relationship requirement.
*/

#include <cmath>
#include <vector>
#include <iostream>

int main()
{
    int n = 10;
    int sum = 0;
    while (n / (std::floor(std::log10(n)) + 1) <= std::pow(9, 5))
    {
        int _n = n;
        int s = 0;
        while (_n > 0)
        {
            s += std::pow(_n % 10, 5);
            _n /= 10;
        }
        if (s == n)
            sum += n;
        n++;
    }

    std::cout << sum;
}
