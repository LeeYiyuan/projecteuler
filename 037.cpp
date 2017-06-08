/*
    Define a left strippable prime as one that remains a prime while digits are
    removed from the left. Similarly, a right strippable prime is one that
    remains a prime while digits are removed from the right.

    We maintain a list of left and right strippable primes separately, starting
    with those of length 1.

    At each step, we extend the primes in each list by one digit in the left and
    right direction respectively. We then collect the prime results, again into
    their respective lists.

    These are guaranteed to be left and right strippable respectively, because
    removing the last digit will give us a prime that was previously left and
    right strippable respectively.

    At each step, we count the number of primes that appear in both lists and
    add that to our hits list. We terminate the process when we have 11 primes.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "prime_util.h"

int main()
{
    std::vector<int> l_primes = { 2, 3, 5, 7 };
    std::vector<int> r_primes = { 2, 3, 5, 7 };

    int sum = 0;
    int count = 0;
    while (count < 11)
    {
        std::vector<int> _l_primes;
        std::vector<int> _r_primes;

        // Exclude 0, because left extending a number by 0 leads to no extension,
        // and right extending anumber by 0 gives a non-prime (divisibility by 10).
        for (int d = 1; d < 10; d++)
        {
            for (int &prime : l_primes)
            {
                int _prime = std::stoi(std::to_string(d) + std::to_string(prime));
                if (util::is_prime(_prime)) _l_primes.emplace_back(_prime);
            }

            for (int &prime : r_primes)
            {
                int _prime = 10 * prime + d;
                if (util::is_prime(_prime)) _r_primes.emplace_back(_prime);
            }
        }

        l_primes = _l_primes;
        r_primes = _r_primes;
        for (int &l_prime : l_primes)
        {
            if (std::find(r_primes.begin(), r_primes.end(), l_prime) != r_primes.end())
            {
                sum += l_prime;
                count++;
            }
        }
    }

    std::cout << sum;
}
