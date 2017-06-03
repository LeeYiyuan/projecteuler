/*
    Let F_n define the sequence of reduced proper fractions with denominator
    at most n.

    According to https://en.wikipedia.org/wiki/Farey_sequence#Next_term,
    there exists a non-recursive formula to generate the terms of F_n.

    We need to consider F_12000.
*/

#include <iostream>

int main()
{
    int n = 12000;

    int count = 0;
    int a = 0, b = 1, c = 1, d = n;
    while (c <= n)
    {
        int k = (n + b) / d;
        int _a = c;
        int _b = d;
        int _c = k * c - a;
        int _d = k * d - b;

        a = _a; b = _b; c = _c; d = _d;

        // a / b > 1 / 3 <=> 3a > b,
        // a / b < 1 / 2 <=> 2a < b
        if (3 * a > b && 2 * a < b)
            count++;
    }

    std::cout << count;
}
