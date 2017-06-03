/*
    Once again, similar to #31, #76, #77.

    Because we expect a ridiculously large n, we shall use dynamic programming just
    like we did in #76. However this time we do all computations modulo 1000000
    because the other digits are irrelevant.

    Except this time, even dynamic programming can't save us! It still runs too slowly
    after testing (at least previously on Python 2.7 before I ported it to C++ here).

    We resort to Number Theory and use the recursive formula given here :
    (https://en.wikipedia.org/wiki/Pentagonal_number_theorem).

    It says that

        p(n) = \sum_{k} (-1)p(n - g_k),
        p(0) = 1,
        p(k) = 0 for k < 0.

    where k = 1, -1, 2, -2, 3, -3, ... and g_k is the kth pentagonal number,

        g_k = k(3k - 1) / 2

    We maintain a list of p with p[n] corresponding to p(n). Additionally, we
    maintain another list of mask and signs, which corresponds to the pentogonal
    offsets required and the signs for these previous terms respectively.
*/

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> p = { 1 };
    std::vector<int> mask;
    std::vector<int> signs;

    int k = 1;
    int g_k = 1;
    int n = 0;

    while (p.back() != 0)
    {
        n++;

        // Process pentagonal number index offsets.
        if (p.size() == g_k)
        {
            mask.emplace_back(g_k);
            signs.emplace_back((std::abs(k) - 1) % 2 == 0 ? 1 : -1);
            k = -k;
            if (k > 0)
                k++;
            g_k = k * (3 * k - 1) / 2;
        }

        // Add previous numbers to get current number.
        int _p = 0;
        for (int i = 0; i < mask.size(); i++)
        {
            _p += signs[i] * p[p.size() - mask[i]];
        }

        p.emplace_back(_p % 1000000);
    }

    std::cout << n;
}
