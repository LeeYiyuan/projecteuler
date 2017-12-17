/*
    Initially I attempted to force out an elliptic curve but thought that was
    too hard. I couldn't think of something that doesn't require some advanced
    mathematics (a category which I think elliptic curves fall under) - Which I
    obviously am not smart enough to even dare to attempt.

    So I gave up and followed http://www.mathblog.dk/project-euler-141, changing
    some variables they used to the ones I have been using in some similar
    attempts of mine.

    The key idea is to express r, d, q as r, r(x / y), r(x^2 / y^2) where gcd(x,
    y) = 1. This shows that y^2 | r since gcd(x^2, y^2) = 1 but y^2 | rx^2. From
    here one can parameterize r = ay^2, d = axy, q = ay^2.

    However I noticed something which I think is erroneous in the article above.
    For the second loop that loops through the denominator of the common ratio a /
    b, the author did an initial check for n = a^3b^2 + b^2 to see if it has
    exceeded the limit.

    I guess this is to check if the minimum value of c in the loop for a
    particular value of (a, b) causes n, which is minimum across c, to exceed
    the limit, and to move to the next value of a if such is the case.

    However in that case I believe the check should be for n = a^3b + b^2, where
    we use a^3b instead of a^3b^2, as we are substituting c = 1 into the formula
    given for n which is n = a^3bc^2 + b^2c.
*/

#include <iostream>
#include <unordered_set>
#include <numeric>
#include <cmath>
#include <cstdint>
#include "number_util.h"

int main()
{
    uint64_t n2_max = 1000000000000ull;
    std::unordered_set<ull> set_n2;
    uint64_t x = 2;
    uint64_t x3 = 8;
    while (x3 < n2_max)
    {
        uint64_t y = 1;
        uint64_t y2 = 1;
        while (y < x && 1 * x3 * y + y2 < n2_max)
        {
            if (util::gcd(x, y) == 1)
            {
                uint64_t a = 1;
                uint64_t a2 = 1;
                uint64_t n2 = a2 * x3 * y + a * y2;
                while (n2 < n2_max)
                {
                    if (std::fmod(std::sqrt(n2), 1) == 0)
                        set_n2.emplace(n2);
                    a++;
                    a2 = a * a;
                    n2 = a2 * x3 * y + a * y2;
                }
            }
            y++;
            y2 = y * y;
        }
        x++;
        x3 = x * x * x;
    }

    std::cout << std::accumulate(set_n2.begin(), set_n2.end(), ull(0));
}
