/*
    Similar to #114, #115, #116, let b_i be the number of ways to fill a length i
    row such that the last tile is black. Let c_i be the number of ways such that
    the last tile is colored either red, green or blue.

    At position i, the previous tile is either colored or not colored. This gives

        b_i = b_{i - 1} + c_{i - 1}

    If the last tile is colored, it is either red, green or blue with lengths
    2, 3, 4 respectively. To make it colored, the tiles up to position
    i - 2, i - 3 and i - 4 respectively must end uncolored (b_{i - 2}, b_{i - 3},
    b_{i - 4}) or colored (c_{i - 2}, c_{i - 3}, c_{i - 4}). This gives

        c_i = b_{i - 2} + b_{i - 3} + b_{i - 4} + c_{i - 2} + c_{i - 3} + c_{i - 4}

    with seed values

        b_1 = 1, b_2 = 1, b_3 = 2, b_4 = 4
        c_1 = 0, c_2 = 1, c_3 = 2, c_4 = 4
*/

#include <vector>
#include <iostream>

typedef unsigned long long ull;

int main()
{
    std::vector<ull> b = { 1, 1, 2, 4 };
    std::vector<ull> c = { 0, 1, 2, 4 };

    for (int i = 4; i < 50; i++)
    {
        ull b_i = b.back() + c.back();
        ull c_i =
            *(b.end() - 2) + *(b.end() - 3) + *(b.end() - 4) +
            *(c.end() - 2) + *(c.end() - 3) + *(c.end() - 4);
        b.emplace_back(b_i);
        c.emplace_back(c_i);
    }

    std::cout << b.back() + c.back();
}
