/*
    We use the technique from #21 to compute divisor sums across a range of
    numbers quickly.

    Then, we filter out the abundant numbers.

    Finally, we create a bit flag array and loop through pairs of abundant
    numbers, each time marking out the entry in the bit flag array that
    corresponds to their sum. We can limit the inner loop corresponding to the
    second item to start not before the first item to remove duplicate cases and
    to reduce our search space.

    We then take the sum of numbers whose corresponding entry in the bit flag
    array is not marked out.
*/

#include <iostream>
#include <vector>

int main()
{
    int limit = 28124;

    // Compute divisor sums.
    std::vector<int> divisor_sums(limit);
    for (int divisor = 1; divisor < limit; divisor++)
    {
        int quotient = 1;
        while ((++quotient) * divisor < limit)
            divisor_sums[quotient * divisor] += divisor;
    }

    // Get abundant numbers.
    std::vector<int> abundant_numbers;
    for (int n = 0; n < limit; n++)
        if (divisor_sums[n] > n)
            abundant_numbers.emplace_back(n);

    // Bit flags to determine if a number is the sum of two abundant numbers.
    std::vector<bool> is_sum(limit);
    for (int i = 0; i < limit && 2 * abundant_numbers[i] < limit; i++)
        for (int j = i; j < limit && abundant_numbers[i] + abundant_numbers[j] < limit; j++)
            is_sum[abundant_numbers[i] + abundant_numbers[j]] = true;


    // Sum up non hits.
    int sum = 0;
    for (int n = 0; n < is_sum.size(); n++)
        if (!is_sum[n])
            sum += n;

    std::cout << sum;
}
