/*
    Naive solution.
*/

#include <vector>
#include <unordered_set>
#include <iostream>

std::vector<int> factorials = {
    1,
    1,
    2 * 1,
    3 * 2 * 1,
    4 * 3 * 2 * 1,
    5 * 4 * 3 * 2 * 1,
    6 * 5 * 4 * 3 * 2 * 1,
    7 * 6 * 5 * 4 * 3 * 2 * 1,
    8 * 7 * 6 * 5 * 4 * 3 * 2 * 1,
    9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1
};

int move_next(int n)
{
    int next = 0;
    while (n > 0)
    {
        next += factorials[n % 10];
        n /= 10;
    }
    return next;
}

int main()
{

    int count = 0;
    for (int n = 1; n < 1000000; n++)
    {
        int a = move_next(n);
        int b = move_next(move_next(n));

        while (a != b)
        {
            a = move_next(a);
            b = move_next(move_next(b));
        }

        int mu = 0;
        a = n;
        while (a != b)
        {
            a = move_next(a);
            b = move_next(b);
            mu++;
        }

        int lam = 1;
        b = move_next(a);
        while (a != b)
        {
            b = move_next(b);
            lam++;
        }

        if (lam + mu == 60)
            count++;
    }

    std::cout << count;
}
