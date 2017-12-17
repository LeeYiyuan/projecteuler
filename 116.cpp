/*
    Somewhat similar to #114 and #115.

    In general, let b_i be the number of ways for a length i row to be filled
    such that the last tile is black, and let c_i be the number of ways for a
    length i row to be filled such that the last tile is colored (red, green,
    blue separately). Then,

        b_i = b_{i - 1} + c_{i - 1}
        c_i = b_{i - m} + c_{i - m}

    where m = 2, 3, 4 for red, green, blue respectively, with seed values

        b_i = 1 for i = 1, 2, ..., m
        c_i = 0 for i = 1, 2, ..., m - 1
        c_m = 1

    The number of ways to fill a length n row is b_n + c_n - 1 for some color.
    The minus 1 is necessary because at least one tile is used, and there is
    exactly one case where less than one tile, i.e. no tile, is used.
*/

#include <vector>
#include <iostream>
#include <cstdint>

uint64_t count_ways(int m, int n)
{
    std::vector<ull> b(m, 1);
    std::vector<ull> c(m, 0);
    c.back() = 1;
    for (int i = m; i < n; i++)
    {
        uint64_t b_i = b.back() + c.back();
        uint64_t c_i = *(b.end() - m) + *(c.end() - m);
        b.emplace_back(b_i);
        c.emplace_back(c_i);
    }
    return b.back() + c.back() - 1;
}

int main()
{
    uint64_t sum = 0;
    for (int m = 2; m <= 4; m++)
        sum += count_ways(m, 50);

    std::cout << sum;
}
