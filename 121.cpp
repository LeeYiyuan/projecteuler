/*
    This is just probability with some algebraic manipulations. Let m be the number
    of turns. Then the probabilities of drawing blue for turns 1, ..., m are

        1/2, 1/3, ..., 1/{m + 1}

    while the probabilities of drawing red are

        1/2, 2/3, ..., m / {m + 1}

    We need more than half of the turns to be blue draws. We loop through the
    combinations of turns with length more than half of m, with each combination
    corresponding to the turns where blue is drawn.

    Let the combination in some step of the loop be c. We start with a value called
    numerator with initial value 1. For d = 2, ..., m + 1, if d is in c, then
    multiply numerator by 1. Else, multiply numerator by d - 1. These correspond
    to blue and red probabilities respectively.

    The final expected probability is the sum of numerators from each step over (m + 1)!.
    The maximum prize sum is then (m + 1)! / numeratorSum.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include "iter_util.h"
#include "number_util.h"

typedef unsigned long long ull;

int main()
{
    int turns = 15;
    ull numerator_sum = 0;

    for (int length = int(std::ceil(double(turns + 1) / 2)); length <= turns; length++)
    {
        std::vector<int> range(turns);
        std::iota(range.begin(), range.end(), 2);
        for (std::vector<int> &combinations : util::get_combinations(range.begin(), range.end(), length))
        {
            ull numerator = 1;
            for (int d = 2; d <= turns + 1; d++)
                if (!std::binary_search(combinations.begin(), combinations.end(), d))
                    numerator *= d - 1;
            numerator_sum += numerator;
        }
    }

    std::cout << util::factorial(ull(turns + 1)) / numerator_sum;
}
