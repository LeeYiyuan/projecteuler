/*
    Instead of using the technique in #12 to factorize every n to calculate d(n)
    from n = 1 to 9999, we loop through the divisors d. For each divisor, we
    loop through quotients q > 1 (for proper division) to deduce that n = dq has
    divisor d. d is then added to the divisor_sums table entry for n.

    The rest is trivial - We go through the list to see which number n has an
    amicable partner n' that is less that is within the required bound and that
    is not equal to n.
*/

#include <iostream>
#include <vector>

int main()
{
    int limit = 10000;
    std::vector<int> divisor_sums(limit);

    for (int divisor = 1; divisor < limit; divisor++)
    {
        int quotient = 1;
        while ((++quotient) * divisor < limit)
            divisor_sums[quotient * divisor] += divisor;
    }

    int sum = 0;
    for (int n = 1; n < limit; n++)
    {
        int divisor_sum = divisor_sums[n];
        if (divisor_sum < limit  && divisor_sum != n && divisor_sums[divisor_sum] == n)
            sum += n;
    }

    std::cout << sum;
}
