/*
    Similar to #114, but this time we make adjustments to the formulas for b_i
    and r_i. In this problem, let m = 50 be the minimum length of red blocks and
    let n be the length of the row we wish to fill.

    There is no change to b_i:

        b_i = b_{i - 1} + r_{i - 1}

    For r_i, we again consider two cases. First, the previous block ends with a
    red section that is at least m units long. This is r_{i - 1}. Second, the
    previous block ends with a red section that is exactly m - 1 units long.
    This is b_{i - m}. Therefore,

        r_i = r_{i - 1} + b_{i - m}

    with seed values

        b_i = 1 for i <= m,
        r_i = 0 for i < m,
        r_m = 1
*/

#include <vector>
#include <iostream>

int main()
{
    int m = 50;
    std::vector<int> b(m, 1);
    std::vector<int> r(m, 0);
    r.back() = 1;
    int n = m;
    while (b.back() + r.back() <= 1000000)
    {
        n++;
        int b_n = b.back() + r.back();
        int r_n = r.back() + *(b.end() - m);
        b.emplace_back(b_n);
        r.emplace_back(r_n);
    }

    std::cout << n;
}
