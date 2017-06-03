/*
    Let b_i and r_i be the number of ways to fill a length i row such that it
    ends with black and red respectively. For red, r_i counts only valid fills,
    i.e. red sections are at least 3 units long.

    For b_i, the previous block must either be black or red. This gives

        b_i = b_{i - 1} + r_{i - 1}

    For r_i, there are two cases. First, the previous block ends with a red section
    that is at least 3 units long. This is r_{i - 1}. Second, the previous block
    ends with a red section that is exactly 2 units long. To do this, we take a
    length i - 3 block ending with black (there are b_{i - 3}) such blocks) and
    we put in two red units. In principle,

        r_i = r_{i - 1} + b_{i - 3}

    with the seed values

        b_1 = 1, b_2 = 1, b_3 = 1
        r_1 = 0, r_2 = 0, r_3 = 1
*/

#include <vector>
#include <iostream>

typedef unsigned long long ull;

int main()
{
    std::vector<ull> b = { 1, 1, 1 };
    std::vector<ull> r = { 0, 0, 1 };

    for (int i = 3; i < 50; i++)
    {
        ull b_i = b.back() + r.back();
        ull r_i = r.back() + *(b.end() - 3);
        b.emplace_back(b_i);
        r.emplace_back(r_i);
    }

    std::cout << b.back() + r.back();
}
