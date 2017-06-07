/*
    Instead, we consider 2x + 2y + 2z which is

        (x + y) + (x + z) + (y + z)

    We search for a^2, b^2, c^2 in order with a^2 > b^2 > c^2 such that:

        1) x + y = a^2

        2) x + z = b^2 with
           y - z = a^2 - b^2 being a perfect square.

        3) y + z = c^2 with
           x - z = a^2 - c^2 being a perfect square, and
           x - y = a^2 - b^2 being a perfect square.

    If, for every candidate (a^2, b^2, c^2) we have that x, y, z are positive
    integers, then we have a sum s = x + y + z or 2s = a^2 + b^2 + c^2. We search
    until a^2 + 2^2 + 1^2 is no less than the smallest 2s found, because any a
    beyond this point will never lead to a 2s smaller than the smallest of the
    previous ones found.
*/

#include <cmath>
#include <iostream>
#include <climits>
#include <algorithm>

bool is_square(int n)
{
    return std::fmod(std::sqrt(n), 1) == 0;
}

std::pair<int, int> search(int a, int b_min)
{
    int b = b_min;
    while (!is_square(a * a + b * b))
        b++;
    return { b, int(std::sqrt(a * a + b * b)) };
}

int main()
{
    int a = 1; // x + y;
    int sum_min = INT_MAX;
    while (sum_min == INT_MAX || a * a + 2 * 2 + 1 * 1 >= 2 * sum_min)
    {
        for (int b = 1; b < a; b++) // x + z
        {
            if (is_square(a * a - b * b)) // y - z
            {
                for (int c = 1; c < b; c++) // y + z
                {
                    if (is_square(a * a - c * c) && is_square(b * b - c * c)) // x - z, x - y
                    {
                        double x = double(a * a + b * b - c * c) / 2;
                        double y = double(a * a - b * b + c * c) / 2;
                        double z = double(-a * a + b * b + c * c) / 2;
                        if (std::fmod(x, 1) == 0 && std::fmod(y, 1) == 0 && std::fmod(z, 1) == 0 && x > 0 && y > 0 && z > 0)
                        {
                            int s = int(x + y + z);
                            sum_min = std::min(sum_min, s);
                        }
                    }
                }
            }
        }
        a++;
    }

    std::cout << sum_min;
}
