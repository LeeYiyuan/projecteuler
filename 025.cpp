/*
    The nth Fibonacci number is given by Binet's Formula,

        F_n = (\phi^n + \psi^n) / \sqrt(5)

    where \phi > 1 and \psi = -1 / \phi. Since -1/2 < \phi^n / sqrt(5) < 1/2,
    for all n >= 0, we have

        F_n - 1/2 < \phi^n / \sqrt(5) < F_n + 1/2

    or

        F_n ~ \phi^n / \sqrt(5)

    for large n, which is valid since we are looking for n >= 10^999.

    So we need

        \floor(n\lg\phi - \lg\sqrt(5)) + 1 >= 1000
        \floor(n\lg\phi - \lg\sqrt(5)) >= 999
        n\lg\phi - \lg\sqrt(5) >= 999
        n \ge (999 + \lg\sqrt(5)) / \lg\phi
        n \ge math.ceil((999 + \lg\sqrt(5)) / \lg\phi)
*/

#include <cmath>
#include <iostream>

int main()
{
    double phi = (1 + std::sqrt(5)) / 2;
    std::cout << int(std::ceil((999 + std::log10(std::sqrt(5))) / std::log10(phi)));
}
