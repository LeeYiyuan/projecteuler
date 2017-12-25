/*
    We brute force the possible coordinates of P and Q, which should be
    reasonable since there are only 50^4 = 6250000 cases. We reject the
    following cases:

        1) If P or Q = 0, or if P = Q, since no triangle will be formed.
        2) If width or height from origin == 0, since no triangle will be
           formed.
        3) If not right angled. This can be done efficiently by computing the
           possible dot products of (OP, OQ), (OP, PQ), (OQ, PQ) and checking
           if at least one is right angled.
        4) If it is already counted. (x_P, y_P, x_Q, y_Q) and (x_Q, y_Q, x_P,
           y_P) are duplicate cases.
*/

#include <vector>
#include <iostream>
#include <utility>
#include <set>
#include <algorithm>

typedef std::pair<int, int> coord_t;
typedef std::pair<coord_t, coord_t> result_t;

bool is_perpendicular(coord_t const &A, coord_t const &B)
{
    return A.first * B.first + A.second * B.second == 0;
}

int main()
{
    int dimension = 50;

    std::set<result_t> results;
    for (int x_1 = 0; x_1 <= dimension; x_1++)
    {
        for (int y_1 = 0; y_1 <= dimension; y_1++)
        {
            for (int x_2 = 0; x_2 <= dimension; x_2++)
            {
                for (int y_2 = 0; y_2 <= dimension; y_2++)
                {
                    coord_t OP(x_1, y_1);
                    coord_t OQ(x_2, y_2);
                    coord_t PQ(x_2 - x_1, y_2 - y_1);
                    int height = std::max(OP.second, OQ.second);
                    int width = std::max(OP.first, OQ.first);

                    // Invalid coordinate pairs.
                    if (OP == coord_t(0, 0) || OQ == coord_t(0, 0) || OP == OQ)
                        continue;

                    // Invalid width or height from origin.
                    if (height == 0 || width == 0)
                        continue;

                    // Not right angled.
                    if (!is_perpendicular(OP, OQ) && !is_perpendicular(OP, PQ) && !is_perpendicular(OQ, PQ))
                        continue;

                    // Is already counted.
                    if (results.find(result_t(OP, OQ)) != results.end())
                        continue;
                    if (results.find(result_t(OQ, OP)) != results.end())
                        continue;

                    results.emplace(OP, OQ);
                }
            }
        }
    }

    std::cout << results.size();
}
