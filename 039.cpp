#include <iostream>
#include <cmath>

int main()
{
    int max_p;
    int max_count = -1;
    for (int p = 3; p <= 1000; p++)
    {
        int count = 0;
        for (int a = 1; a < p; a++)
        {
            /*
                Start with the largest possible b, and therefore the smallest
                possible c. This maximum assumes c is at least 1 which is
                necessary.
            */
            int b = p - a - 1;
            /*
                Decrement b, at the same time increasing c, until c^2 >= a^2 +
                b^2. It may possible to use binary search here instead of linear
                search.
            */
            while (b > 1 &&  std::pow(p - a - b, 2) < a * a + b * b)
                b--;
            int c = p - a - b;
            if (a * a + b * b == c * c)
                count++;
        }
        if (count > max_count)
        {
            max_p = p;
            max_count = count;
        }
        /*
            Note that we are double counting solutions, but this double counting
            is consistent, in particular (a, b, c) = (b, a, c). a and b will
            never be the same because the square root of 2 is irrational, so
            there will never be a case (a, a, c) that is not double counted,
            because it will never be a solution.
        */
    }

    std::cout << max_p;
}
