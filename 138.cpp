/*
    Similar to #94 so we try and use the same approach of formulating a Pell equation
    with the provided requirements.

        h^2 = l^2 - (b/2)^2
        4h^2 = 4l^2 - b^2
        4(b \pm 1)^2 + b^2 - 4l^2 = 0
        4b^2 \pm 8b + 4 + b^2 - 4l^2 = 0
        5b^2 \pm 8b + 4 - 4l^2 = 0
        25b^2 \pm 40b + 20 - 20l^2 = 0
        (5b \pm 4)^2 + 20 - 16 - 20l^2 = 0
        (5b \pm 4)^2 - 20l^2 = -4

    This gives us a Pell equation x^2 - 20y^2 = -4. For every solution (x, y), we
    have (x, y) = (5b \pm 4, l).
*/

#include <iostream>
#include <gmpxx.h>
#include <vector>
#include "pell_util.h"

int main()
{
    int count_L = 0;
    mpz_class sum_L = 0;
    pell_solver solver(20, -4);
    while (solver.move_next())
    {
        mpz_class x = solver.solution.x;
        mpz_class y = solver.solution.y;
        std::vector<int> polarities = { -1, 1};
        for (int &polarity : polarities)
        {
            mpz_class b = x + polarity % 4;
            if (b % 5 == 0)
            {
                b /= 5;
                // Because we are solving b with x = 5b \pm 4, we flip the polarity.
                mpz_class h = b - polarity;
                mpz_class l = y;
                if (b > 0 && h > 0 && l > 0)
                {
                    count_L++;
                    sum_L += l;
                    if (count_L == 12)
                    {
                        std::cout << sum_L;
                        return 0;
                    }
                }
            }
        }
    }
}
