/*
    By Lucas' Theorem (https://en.wikipedia.org/wiki/Lucas%27s_theorem), we need
    all (m, n) such that in the base 7 expansion of m, n, each digit of
    n are at most the corresponding digits of m. Furthermore, there is an inclusive
    limit of m = 10^9 - 1 = (33531600615)_7.

    Let the base 7 expansions of m and n be respectively:

        m = m_0 * 7^0 + m_1 * 7^1 + ...
        n = n_0 * 7^0 + n_1 * 7^1 + ...

    Let a(d) be the number of non-negative integers less than or equal to d. Then
    a(d) = d + 1.

    Let b(k) be the number of (m, n) pairs whose base 7 expansion has length k,
    where leading zeroes are allowed. Then

        b(k) = (a(0) + a(1) + ... + a(6)) ^ k
             = (1 + 2 + ... + 7)^k
             = 28^k

    We need the number of (m, n) with m <= (33531600615)_7 and 0 <= n <= m. By
    considering the valid digit expansions of each of m, n, this is

        (a(0) + ... + a(2))b(10) + a(3)(
            (a(0) + ... + a(2))b(9) + a(3)(
                (a(0) + ... + a(4))b(8) + a(5)(
                    ...
                        (a(0) + ... + a(4))b(0) + a(5)
                )
            )
        )

        =

        c(2)b(10) + a(3)(
            c(2)b(9) + a(3)(
                c(4)b(8) + a(5)(
                    ...
                        c(4)b(0) + a(5)
                )
            )
        )

    with c(d) = a(0) + ... + a(d) =(d + 1)(d + 2) / 2. The nested expression shall
    be calculated from the inside out.
*/

#include <iostream>
#include <vector>

typedef unsigned long long ull;

ull a(int d)
{
    return d + 1;
}

ull b(int k)
{
    ull result = 1;
    for (int i = 0; i < k; i++)
        result *= 28;
    return result;
}

ull c(int d)
{
    return (d + 1) * (d + 2) / 2;
}

int main()
{
    std::vector<int> limit = { 5, 1, 6, 0, 0, 6, 1, 3, 5, 3, 3 };
    ull count = 1;
    for (int i = 0; i < limit.size(); i++)
    {
        int d = limit[i];
        count *= a(d);
        count += c(d - 1) * b(i);
    }

    std::cout << count;
}
