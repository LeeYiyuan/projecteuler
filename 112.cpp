/*
    Notice that a number is bouncy if and only if its reverse is bouncy. This lets
    us optimize bounciness determination by using modulo and division by 10 operations
    instead of string operations.
*/

#include <iostream>

bool is_bouncy(int n)
{
    bool is_increasing = true;
    bool is_decreasing = true;

    int digit = n % 10;
    n /= 10;
    while ((is_increasing || is_decreasing) && n > 0)
    {
        int _digit = n % 10;
        n /= 10;
        if (is_increasing && _digit > digit)
            is_increasing = false;
        if (is_decreasing && _digit < digit)
            is_decreasing = false;
        digit = _digit;
    }

    return !(is_increasing || is_decreasing);
}

int main()
{
    int total = 99;
    int count = 0;
    int n = 99;

    // count / total < 0.99 <=> 100 * count < 99 * total.
    while (100 * count < 99 * total)
    {
        n++;
        if (is_bouncy(n))
            count++;
        total++;
    }

    std::cout << n;
}
