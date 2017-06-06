/*
    Label the spirals 1, 2, 3, ... with spiral 1 having only one element, namely 1.
    Note that the length of spiral n is given by

        l_n = 2n - 1

    where l_1 = 1.

    We start at the end of spiral 1, namely step 1, and move 2 steps to reach the
    element in spiral 2 at the top right
    diagonal. We then move 2 more steps to the top left, bottom left and bottom
    right diagonals.

    We are now at the end of spiral 2. We then move 4 steps to get the element
    in spiral 3 at the top right diagonal. 4 more steps is needed for each of
    the top left, bottom left and bottom right diagonals sequantially.

    In general, for spiral n > 1, we need 2(n - 1) steps between each diagonal.
    This allows us to traverse the spiral systematically.

    This is the first problem where I switched the primality testing from a
    dynamically expanding list of primes to Miller-Rabin (deterministic), because
    the expanding list of primes proved to be too slow even with a lookup table.
*/

#include <iostream>
#include "prime_util.h"

int main()
{
    // We start at the end of spiral 1.
    int n = 1; // Spiral number.
    int step = 1; // Step number.
    int diagonal_count = 1;
    int prime_count = 0;

    // Force 1.0 to bypass initial ratio check which will fail for
    // primeCount / diagonalCount = 0 / 1 < 0.1.
    double ratio = 1.0;
    while (ratio > 0.1)
    {
        n++;
        for (int i = 0; i < 4; i++)
        {
            step += 2 * (n - 1);
            if (i != 3) // Top right, top left or bottom left arm.
                if (util::is_prime(step))
                    prime_count++;
            diagonal_count++;
        }
        ratio = (prime_count * 1.0) / diagonal_count;
    }

    std::cout << 2 * n - 1;
}
