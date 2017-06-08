/*
    First, we prove that A(n) < n + 2 in order to impose a lower bound on our
    search. For some n, let k be the minimum positive integer such that n
    divides R(k).

    Suppose that k >= n + 2. Then for i = 1, 2, ..., n + 1, there exists n + 1
    different remainders of R(i) modulo n. By the Pigeonhole Principle, there
    are only n residues modulo n, and thus at least two of R(i) must have the
    same remainder. Denote two of these repunits as R(a) and R(b) with a < b
    without loss of generality.

    Then, for some positive integer c, we have

        R(b) - R(a) = 10^c R(b - a)

    Since R(b) and R(a) have the same remainder modulo n, their differences are
    equivalent to zero modulo n. That is,

        10^c R(b - a) \equiv 0 \pmod n

    Since GCD(n, 10) == 1, n does not divide 10^c. But n divides 10^c R(b - a)
    and thus it must divide R(b - a). Since b - a < k, there exists another
    exponent, namely d < k, such that n | R(d), leading to a contradiction.

    Therefore, A(n) < n + 2. Since A(n) > 1000000, we start our search with

        n >= 999999

    Fortunately, the required n lies very close to this lower bound so we need
    not implement any super high powered solution.

    To calculate A(n) we use multiplication by 10 followed by addition by 1
    modulo n until the residue equals 1. The number of steps taken is exactly
    A(n).
*/

#include <iostream>

int A(int n)
{
    int residue = 1;
    int k = 1;
    while (residue != 0)
    {
        residue = (10 * residue + 1) % n;
        k++;
    }
    return k;
}

int main()
{
    int n = 999999;
    while (true)
    {
        if (n % 2 != 0 && n % 5 != 0)
        {
            if (A(n) > 1000000)
            {
                std::cout << n;
                return 0;
            }
        }
        n++;
    }
}
