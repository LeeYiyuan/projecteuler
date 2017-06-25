/*
    It is possible to characterize every positive integer according to their
    unique prime factorizations.

    Let the unique prime factorization of some positive integer n be [e_2, e_3,
    e_5, ...] where n = 2^e_2 * 3^e_3 * 5^e_5 *.... Then the number of unique
    factor pairs of n^2, fp(n^2) disregarding order, is

        fp(n^2) = ((2 * e_2 + 1) * (2 * e_3 + 1) * (2 * e_5 + 1) ... + 1) / 2

    We use depth first search on (e_2, e_3, e_5, ...). A leaf of the search tree
    is reached if either of the conditions are met:

        1) e_i >= e_{i - 1}. This is because if, for example e_5 > e_3, we can
           swap e_5 with e_3 to get a smaller n while maintaining fp(n^2). As
           such we are only concerned about non-increasing (e_2, e_3, e_5, ...).
        2) The computed value of fp(n^2) using the exponents thusfar exceeds
           4000000. This is because appending any more exponents will only cause
           n to increase while fp(n^2) remains larger than 4000000; And thus,
           any further n due to appended exponents will not be smaller than the
           current hit value of n.
        3) The computed value of n using exponents thusfar exceeds the n value
           of hits previously found. This is because adding any more exponent
           will cause the current value of n to be more than that of a
           previously found hit, so it will not be the smallest value of n.

    We take the minimum n among leaves such that e_i <= e_{i - 1} and fp(n^2) >
    4000000.
*/

#include <iostream>
#include <vector>
#include <gmpxx.h>
#include <climits>
#include "prime_util.h"
#include "number_util.h"

std::vector<int> primes = util::get_primes(1000);

int count_factor_pairs(std::vector<int> const &exponents)
{
    int product = 1;
    for (int const &exponent : exponents)
        product *= 2 * exponent + 1;
    return (product + 1) / 2;
}

mpz_class get_number(std::vector<int> const &exponents)
{
    mpz_class n = 1;
    for (int i = 0; i < exponents.size(); i++)
        n *= util::pow(primes[i], exponents[i]);
    return n;
}

void search(std::vector<int> const &exponents, int factor_pairs_minimum_count, mpz_class &number_limit, std::vector<mpz_class> &results)
{
    int exponent = 1;
    int exponent_limit = exponents.size() == 0 ? INT_MAX : exponents.back();


    while (true)
    {
        if (exponent > exponent_limit)
            return;

        std::vector<int> _exponents(exponents);
        _exponents.emplace_back(exponent);

        if (number_limit != -1 && get_number(_exponents) >= number_limit)
            break;

        if (count_factor_pairs(_exponents) > factor_pairs_minimum_count)
        {
            mpz_class result = get_number(_exponents);
            results.emplace_back(result);
            if (number_limit == -1 || result < number_limit)
                number_limit = result;
            break;
        }

        search(_exponents, factor_pairs_minimum_count, number_limit, results);

        exponent++;
    }
}

int main()
{
    std::vector<int> exponents;
    mpz_class number_limit = -1;
    std::vector<mpz_class> results;
    search(exponents,  4000000, number_limit, results);

    std::cout << *std::min_element(results.begin(), results.end());
}
