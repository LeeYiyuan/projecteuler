/*
    We consider instead the pattern of each arm of the diagonals individually.

    Starting with the inner most spiral of dimension 1, there are a total of
    (1001 + 1) / 2 = 501 spirals, with dimensions 1, 3, ..., 1001. We shall
    number the spirals, with spiral n having dimension 2n - 1.

    First, the arm extending towards the bottom right. The distance between the
    element of spiral n and the element of spiral n + 1 is given by

        3((2n - 1) - 1) + ((2n + 1) - 1)
        = 8n - 6

    So we have, where a_n is the element of spiral n on the bottom right arm:

        a_{n + 1} - a_n = 8n - 6
        a_n - a_1 = \sum_{i = 1} ^ {n - 1} (8n - 6)
        a_n - 1   = 4n(n-1) - 6(n-1)
        a_n       = 4n^2 - 10n + 7

    Secondly, note that the element of spiral n lying on the bottom left (b_n),
    top left (c_n) and top right (d_n) arms are 2n - 2, 4n - 4 and 6n - 6 more
    than a_n. As such,

        b_n = 4n^2 - 8n + 5
        c_n = 4n^2 - 6n + 3
        d_n = 4n^2 - 4n + 1

    Therefore, the required sum is

        \sum_{i = 1}^501 (a_i + b_i + c_i + d_i) - 3
        = \sum_{i = 1}^501 (16i^2 - 28i + 16) - 3

    The -3 at the back is because we have overcounted the common element of each
    each spiral, namely 1 in spiral 1, 3 times. So we deduct these from the
    overall sum. Using Faulhaber's formulas, this is

        16(501)(501 + 1)(2 * 501 + 1) / 6 - 28(501)(501 + 1) / 2 + 16 * 501
*/

#include <iostream>

int main()
{
    unsigned long long n = 501;
    std::cout << 16 * n * (n + 1) * (2 * n + 1) / 6 - 28 * n * (n + 1) / 2 + 16 * n - 3;
}
