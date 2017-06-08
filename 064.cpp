/*
    We track a, the coefficients of the continued fraction and c[0, 1], which
    contains information about the rationalized fraction at every step, in
    particular

        (sqrt(n) + c[0]) / c[1]

    With this, we can move to the next level of the continued fraction using the
    derivable formulas:

        a = floor((sqrt(n) + c[0]) / c[1])
        c[0] = a * c[1] - c[0]
        c[1] = (n - c[0] ^ 2) / c[1]

    and the coefficients repeat whenever c turns into the initial one.
*/

#include <cmath>
#include <iostream>
#include <vector>
#include <numeric>

int get_period(int n)
{
    std::vector<int> coefficients;
    int a = int(std::sqrt(n));
    std::vector<int> c_initial = { a, n - a * a };
    std::vector<int> c(c_initial);
    while (coefficients.empty() || c != c_initial)
    {
        a = int(std::floor((std::sqrt(n) + c[0]) / c[1]));
        c[0] = a * c[1] - c[0];
        c[1] = (n - c[0] * c[0]) / c[1];
        coefficients.emplace_back(a);
    }
    return coefficients.size();
}

int main()
{
    int hits = 0;
    for (int n = 2; n <= 10000; n++)
        if (std::fmod(std::sqrt(n), 1) != 0)
            if (get_period(n) % 2 == 1)
                hits++;

    std::cout << hits << std::endl;
}
