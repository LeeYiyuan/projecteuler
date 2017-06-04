#include <iostream>
#include <cmath>

unsigned long long get_triangular(unsigned long long n)
{
    return n * (n + 1) / 2;
}

bool is_pentagonal(unsigned long long p_n)
{
    // Solution to 3n^2 - n - 2p_n = 0.
    double n = (1 + std::sqrt(1 + 24 * p_n)) / 6;
    return (unsigned long long)(n) == n;
}

bool is_hexagonal(unsigned long long h_n)
{
    // Solution to 2n^2 - n - h_n = 0
    double n = (1 + std::sqrt(1 + 8 * h_n)) / 4;
    return (unsigned long long)(n) == n;
}

int main()
{
    int n = 286;
    int t_n = get_triangular(n);
    while (!is_pentagonal(t_n) || !is_hexagonal(t_n))
    {
        n++;
        t_n = get_triangular(n);
    }

    std::cout << t_n;
}
