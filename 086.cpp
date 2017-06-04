/*
    Label the front facing side of the cuboid side 1, the left facing
    side of the cuboid side 2 and the bottom facing side of the cuboid side 3.
    We shall label the face opposite side n as side n'.

    The possible shortest routes are

        (1, 3'), (1, 2'), (2, 1'), (2, 3'), (3, 1'), (3, 2')

    The distance of the route (x, y) is the same as (y', x'). So our possible
    shortest routes are really just the shortest among

        (1, 3'), (1, 2'), (3, 2')

    Label the dimensions of the cuboid a by b by c in the x, y, z directions
    respectively. By stacking the faces on top of or beside each other and using
    the Triangle Inequality, we can show that the shortest lengths d for each route
    are given by:

        (1, 3') -> d^2 = a^2 + (c + b)^2 = a^2 + b^2 + c^2 + 2cb
        (1, 2') -> d^2 = c^2 + (a + b)^2 = a^2 + b^2 + c^2 + 2ab
        (3, 2') -> d^2 = b^2 + (a + c)^2 = a^2 + b^2 + c^2 + 2ac

    Therefore, the solution can be restated to finding (a, b, c) for which the
    minimum of a^2 + (b + c)^2, b^2 + (c + a)^2, c^2 + (a + b)^2 is an integer.

    Given a hit (a, b, c), every permutation of (a, b, c) will be a hit as well
    because the length of the minimal path remains the same. Actually, we need
    not even consider these permutations because they all correspond to rotations
    of the cuboid with dimensions a, b, c.

    As such, we can simplify our problem further to finding integer triplies (a, b, c)
    such that 1 <= a <= b <= c <= M. But with this we can essentially eliminate
    the need to find the lengths of the three possible routes, beacuse we know
    that the shortest route will be given by (1, 2') for which 2ab < 2ac, 2cb.

    So we only need to check for 1 <= a <= b <= c <= M, if a^2 + b^2 + c^2 + 2ab
    is a perfect square. For every such (a, b, c), we add 1 to the total number
    of solutions.

    We need to find the least M for which the total number of solutions exceeds 1000000.

    We start from M = 1 where the only candidate is (1, 1, 1), and increment M
    by one at the start end of every step.

    At step M > 1, the solutions (a, b, c) either contain M or do not contain M.
    Those that do not contain M have a, b, c all less than M and are exactly
    the solutions up to the previous step. So we only need to check tuples (a, b, c)
    where at least one of (a, b, c) is equal to M. Given that we only need a <= b <= c,
    we essentially have to check only:

        (a, b, M), (a, M, M), (M, M, M)

    where a <= b < M. Note that the last one is never a solution. This reduces to

        (a, b, M) where a <= b <= M, a != M

    We add the number of solutions to the total number of solutions and move on to
    the next step.

    Note further that for every sum s = a + b, if

        d^2 = a^2 + b^2 + c^2 + 2ab
            = s^2 + c^2

    is a perfect square, then every a, b that sum up to s will give a solution. So
    we can first look for the sums s that satisfy the required condition, and then
    count valid (a, b) that sum up to s.

    At the start of each step we check if total number of solutions has exceeded
    1000000, and terminate if so.
*/

#include <cmath>
#include <iostream>

int main()
{
    int n_solutions = 0;
    int M = 0;
    while (n_solutions <= 1000000)
    {
        M++;
        for (int s = 2; s <= 2 * M - 1; s++)
        {
            int d_squared = s * s + M * M;
            if (std::fmod(std::sqrt(d_squared), 1) == 0)
                for (int a = 1; a <= s && a < M && s - a >= a; a++)
                    if (s - a <= M)
                        n_solutions++;
        }
    }

    std::cout << M;
}
