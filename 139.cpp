/*
    We consider without loss of generality triples (a, b, c) such that a, b < c.
    The tiles will have length \pm(b - a), depending on whether a or b is
    larger, and we need this to divide c. Note that we only need consider
    primitive triples because if \pm(b - a() | c, then \pm(kb - ka) | kc for
    every positive integer k.

    First parametrize our primitive triples (a, b, c) using Euclid's formula:

        a = m^2 - n^2
        b = 2mn
        c = m^2 + n^2

    where m > n > 0 , (m, n) = 1, and m, n are not both odd. Then for some
    positive integer d we need

        d(b - a) = c , -d(b - a) = c
        d(2mn - m^2 + n^2) = m^2 + n^2 , -d(2mn - m^2 + n^2) = m^2 + n^2
        2dmn - dm^2 + dn^2 = m^2 + n^2 , -2dmn + dm^2 - dn^2 = m^2 + n^2
        (d - 1)n^2 + 2dmn - (d + 1)m^2 = 0 , (d + 1)n^2 + 2dmn - (d - 1)m^2 = 0
        (d + 1)m^2 - 2dmn - (d - 1)n^2 = 0 , (d - 1)m^2 - 2dmn - (d + 1)n^2 = 0

    Taking discriminants with respect to m respectively, we have

        (-2dn)^2 + 4(d + 1)(d - 1)n^2,  (-2dn)^2 + 4(d - 1)(d + 1)n^2
      = 4n^2(2d^2 - 1)

    In order for m to be a perfect square, we required 2d^2 - 1 to be a perfect
    square. That is for some non-negative integer e,

        2d^2 - 1 = e^2
        e^2 - 2d^2 = -1

    For every positive integer solution (e, d), we have again

        m = (2dn \pm 2ne) / 2(d + 1) , (2dn \pm 2ne) / 2(d - 1)
          = n * (d \pm e) / (d + 1) , n * (d \pm e) / (d - 1)
          = n * (d + e) / (d + 1) , n * (d + e) / (d - 1)

    noting that the case with -e instead of +e is rejected because e > d and
    thus d - e < 0. if e = 1, then from the Pell equation we have d = 1. For the
    first case, m = n and for the second, there are no solutions to m. Hence we
    only consider e > 1, in which case d > 1. For the first case, m > n and for
    the second, there is a solution to m.

    By rearranging m as an expression of n into a ratio,

        m / n = (d + e) / (d + 1), (d + e) / (d - 1)

    so in fact, the candidates (m, n) for (e, d) are exactly multiples of (f1,
    g1) and (f2, g2), where f1 / g1 and f2 / g2 are the reduced fractions of (d +
    e) / (d + 1) and (d + e) / (d - 1) respectively. However, since we need
    gcd(m, n) = 1, we cannot have multiples of (f1, g1) or (f2, g2). Thus, there
    are only two candidates for (m, n), namely (f1, g1), (f2, g2).

    To recap,

        1) Find (e, d) as solutions to e^2 - 2d^2 - 1. We can stop when d
           exceeds the perimeter limit, because then c will exceed the perimeter
           limit and thus the permiter will exceed the perimeter limit.
        2) For each (e, d), list candidates (m, n) = (f1, g1), (f2, g2) where
           f1 / g1, f2 / g2 are the reduced fractions of (d + e) / (d + 1),
           (d + e) / (d - 1) respectively.
        3) Eliminate candidates where both m, n are odd.
        4) For remaining candidates (m, n), find (a, b, c) according to Euclid's
           formula.
        5) Add floor(perimiter_limit / (a + b + c)) to total count.
        6) Print total count as answer.
*/

#include <iostream>
#include <vector>
#include <gmpxx.h>
#include <utility>
#include "gmp_util.h"
#include "number_util.h"
#include "pell_util.h"

int main()
{
    mpz_class perimeter_limit = 100000000;
    int count = 0;
    util::pell_solver solver(2, -1);
    while (solver.move_next())
    {
        mpz_class e = solver.solution.x;
        mpz_class d = solver.solution.y;

        if (d >= perimeter_limit)
            break;

        if (e > 1)
        {
            std::vector<std::pair<mpz_class, mpz_class>> candidates;

            mpz_class h1 = util::gcd(mpz_class(d + e), mpz_class(d + 1));
            candidates.emplace_back((d + e) / h1, (d + 1) / h1);
            mpz_class h2 = util::gcd(mpz_class(d + e), mpz_class(d - 1));
            candidates.emplace_back((d + e) / h2, (d - 1) / h2);

            for (std::pair<mpz_class, mpz_class> &candidate : candidates)
            {
                mpz_class m = candidate.first;
                mpz_class n = candidate.second;
                if (m % 2 == 0 || n % 2 == 0)
                {
                    mpz_class a = m * m - n * n;
                    mpz_class b = 2 * m * n;
                    mpz_class c = m * m + n * n;
                    mpz_class perimeter = a + b + c;
                    count += util::mpz_to<int>(perimeter_limit / perimeter);
                }
            }
        }
    }

    std::cout << count;
}
