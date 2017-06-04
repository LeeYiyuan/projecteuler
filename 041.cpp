/*
    The sum of digits of a n-digit pandigital number is n(n + 1) / 2.

    For n = 2, 3, 5, 6, 8, 9, the sum is divisible by 3. Since a number is
    divisible by 3 iff the sum of its digits is divisible by 3, we expect
    pandigital primes only with 1, 4 or 7 digits.

    We search up to and including 7 digits anyway, neglecting a skip for 2, 3, 5, 6
    digits because they make up less than 12% of 7 digit numbers so it isn't all
    that bad.
*/

#include <iostream>
#include <vector>
#include <string>
#include "prime_util.h"

int main()
{
    std::vector<int> primes = get_primes(9999999);

    int max_pandigital_prime = -1;
    for (int &prime : primes)
    {
        std::string prime_string = std::to_string(prime);

        std::vector<char> pandigital_digits;
        for (int d = 1; d <= prime_string.length(); d++)
            pandigital_digits.emplace_back(d + '0');

        if (std::is_permutation(prime_string.begin(), prime_string.end(), pandigital_digits.begin()))
            max_pandigital_prime = std::max(max_pandigital_prime, prime);

    }

    std::cout << max_pandigital_prime;
}
