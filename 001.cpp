/*
We need the sum of multiples of 3 or 5 below 1000.

Consider the multiples of 3 and the multiples of 5. Each set shares a particular
common subset, that is the multiples of 15.

If we add all the numbers in both sets together, we would have the sum of
all multiples of 3 or 5, but the multiples of 15 would have been counted twice.

So we have to subtract off the double count of the multiples of 15 from the
sum of the elements of the two sets.

Hence we need

    sum = 3 * (1 + 2 + ... + 333) + 5 * (1 + 2 + ... + 199) - 15 * (1 + 2 + ... + 66)
        = 3 * (333 * 334) / 2 + 5 * (199 * 200) / 2 - 15 * (66 * 67) / 2
*/

#include <iostream>

int main()
{
    std::cout << 3 * (333 * 334) / 2 + 5 * (199 * 200) / 2 - 15 * (66 * 67) / 2;
}
