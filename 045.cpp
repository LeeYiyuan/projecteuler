#include <iostream>
#include <cmath>
#include <cstdint>

uint64_t get_triangular(uint64_t n)
{
    return n * (n + 1) / 2;
}

bool is_pentagonal(uint64_t p_n)
{
    // Solution to 3n^2 - n - 2p_n = 0.
    double n = (1 + std::sqrt(1 + 24 * p_n)) / 6;
    return (uint64_t)(n) == n;
}

bool is_hexagonal(uint64_t h_n)
{
    // Solution to 2n^2 - n - h_n = 0
    double n = (1 + std::sqrt(1 + 8 * h_n)) / 4;
    return (uint64_t)(n) == n;
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
