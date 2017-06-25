/*
    ============================================================================
                                     THEOREM 1
    ============================================================================
    THEOREM: Let x/y be a reduced fraction. If x/y is the sum of reciprocals
    of squares of distinct integers greater than 1, i.e.

        x/y = 1/a_1 + 1/a_2 + ... + 1/a_k

    Suppose for some prime factor p of y, p^n is the highest power of p that
    divides y. Then p^n must divide at least one of a_i.

    PROOF: Let p^n be a factor of y such that p^n is the highest power of p that
    divides y. The reduced denominator of the RHS divides the LCM(a_1, ...,
    a_k). But this reduced denominator is exactly y. Hence y divides LCM(a_1, ...,
    a_k).

    Suppose for the sake of contradiction that p^n does not divide any of a_1, ...,
    a_k. Then the highest power of p that divides LCM(a_1, ..., a_k) is less
    than n. Hence, p^n will not divide LCM(a_1, ..., a_k), and thus the reduced
    denominator y that divides LCM(a_1, ..., a_k) cannot be divisible by p^n,
    leading to a contradiction since p^n divides y.

    ============================================================================
                                     THEOREM 2
    ============================================================================
    THEOREM: Supposed 1/m^2 is contained among 1/2 = 1/a_1^2 + ... + 1/a_k^2.
    Let p != 2 be a prime divisor of m and let p^n be the greatest power of p
    that divides m. Let b_1, b_2, ... be all the terms among a_1, ... a_k such
    that:

        1) b_i != m
        2) b_i is a multiple of p^n

    Then, p^{2n - 1} must not divide 1/m^2 + 1/b_1^1 + 1/b_2^2 + ....

    PROOF: Suppose instead that  1/m^2 + 1/b_1^2 + 1/b_2^2 + ... is divisible by
    p^{2n - 1} We move everything to the left such that the remaining terms of
    a_i do not contain any multiples of p^n.

    On the LHS, we have 1/2 - 1/m^2 - 1/b_^2 - 1/b_2^2 - .... Since p != 2, it
    is trivial to show that the reduced denominator of the LHS is also divisible
    by p^{2n - 1}. As a trivial but not so direct consequence of theorem 1,
    there must be some term among the remaining a_i such that p^n divides a_i.

    This leads to a contradiction because we have moved all such terms to the LHS.

    ================================================================================
                                REDUCE ALGORITHM
    ================================================================================
    With theorem 2, we can determine which terms from 2-80 are not allowed to be
    included in the sum. Firstly we shall ignore perfect powers of 2 because we
    do not want to elminate all factors of 2 completely in the denominator of
    the sum (we need it to be 1/2).

    For every n within 2-80 that are not perfect powers of 2, we look for p != 2
    that divides n. For every such p, let p^e be the largest power that divides
    n. Then, we check if there is a combination b_1, b_2, ... of multiples of
    p^n among 2-80 except for n such that

        1/n^2 + 1/b_1^2 + 1/b_2^2 + ...

    does not contain a factor of p^{2e - 1}.

    If for all prime p there is at least one such combination, then n is allowed
    as a term. If not, it is not allowed as a term.

    ================================================================================
                                SEARCH ALGORITHM
    ================================================================================
    We can group the allowed terms into multiples of primes. Interestingly for
    2-80, all allowed terms only have prime factors of 3, 5, 7, 13. Again we
    will ignore 2 because we don't want to eliminate 2 from the denominator.

    We start with an availablity list and for each prime factor p, we decide on
    the multiples of p that are present. These are the multiples whose
    reciprocal squared have p eliminated from the reduced denominator. All
    multiples of p are removed from the availability list and selected multiples
    are collected.

    This is done recursively until all prime factors have been considered. For
    each collected list, if there exists such a sum among {1/2^2, 1/4^2, 1/8^2,
    1/16^2, 1/32^2, 1/64^2} such that this sum together with that of the
    collected list is equal to 1/2, then we have a hit.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <gmpxx.h>
#include <algorithm>
#include "prime_util.h"
#include "iter_util.h"
#include "number_util.h"

struct group_struct
{
    std::vector<int> combination;
    mpq_class s;
    group_struct(std::vector<int> &combination, mpq_class s)
    {
        this->combination = combination;
        this->s = s;
    }
};

std::vector<group_struct> get_eliminating_groups(std::vector<int> const &available_terms, mpq_class fraction, int polarity, int p, int e)
{
    std::vector<group_struct> groups;

    std::vector<int> terms;
    for (int const &term : available_terms)
        if (term % util::pow(p, e) == 0)
            terms.emplace_back(term);
    for (int length = 0; length <= terms.size(); length++)
    {
        for (std::vector<int> &combination : util::get_combinations(terms.begin(), terms.end(), length))
        {
            mpq_class s = fraction;
            for (int &term : combination)
                s += polarity * mpq_class(1, term * term);
            if (s.get_den() % util::pow(p, 2 * e - 1) != 0)
                groups.emplace_back(combination, s);
        }
    }

    return groups;
}

// Same as above, but short circuits when the first eliminating group is found.
bool check_eliminating_groups(std::vector<int> const &available_terms, mpq_class fraction, int polarity, int p, int e)
{
    std::vector<int> terms;
    for (int const &term : available_terms)
        if (term % util::pow(p, e) == 0)
            terms.emplace_back(term);
    for (int length = 0; length <= terms.size(); length++)
    {
        for (std::vector<int> &combination : util::get_combinations(terms.begin(), terms.end(), length))
        {
            mpq_class s = fraction;
            for (int &term : combination)
                s += polarity * mpq_class(1, term * term);
            if (s.get_den() % util::pow(p, 2 * e - 1) != 0)
                if (combination.size() > 0)
                    return true;
        }
    }
    return false;
}

bool is_allowed(std::vector<int> const &primes, std::vector<int> const &available_terms, int term)
{
    for (int const &p : primes)
    {
        if (term % p == 0)
        {
            int _term = term;
            int e = 0;
            while (_term % p == 0)
            {
                e++;
                _term /= p;
            }

            std::vector<int> _available_terms;
            for (int const &t : available_terms)
                if (t != term)
                    _available_terms.emplace_back(t);
            if (!check_eliminating_groups(_available_terms, mpq_class(1, term * term), 1, p, e))
                return false;
        }
    }
    return true;
}

std::vector<int> reduce(std::vector<int> const &primes, std::vector<int> const &terms)
{
    std::vector<int> _terms;
    for (int const &term : terms)
        if (is_allowed(primes, terms, term))
            _terms.emplace_back(term);
    return _terms;
}

void search(std::vector<int> const &available_terms, mpq_class fraction, std::vector<int> const &primes, std::vector<mpq_class> &results)
{
    if (primes.size() == 0)
    {
        results.emplace_back(fraction);
        return;
    }

    int p = primes[0];
    std::vector<int> _primes(primes.begin() + 1, primes.end());

    for (group_struct &group : get_eliminating_groups(available_terms, fraction, -1, p, 1))
    {
        std::vector<int> _available_terms;
        for (int const &t : available_terms)
            if (t % p != 0)
                _available_terms.emplace_back(t);
        mpq_class _fraction = group.s;
        search(_available_terms, _fraction, _primes, results);
    }
}

int main()
{
    int limit = 80;
    std::vector<int> primes = util::get_primes(limit);
    primes.erase(primes.begin());

    std::vector<int> terms;
    for (int n = 2; n <= limit; n++)
    {
        double exponent = std::log2(n);
        if (std::fmod(exponent, 1) != 0)
            terms.emplace_back(n);
    }
    terms = reduce(primes, terms);

    std::vector<mpq_class> valid_results;
    std::vector<int> two_powers;
    int two_power = 1;
    while ((two_power *= 2) <= limit)
        two_powers.emplace_back(two_power);

    for (int length = 0; length <= two_powers.size(); length++)
    {
        for (std::vector<int> &combination : util::get_combinations(two_powers.begin(), two_powers.end(), length))
        {
            valid_results.emplace_back(0);
            for (int &term : combination)
                valid_results.back() += mpq_class(1, term * term);
        }
    }

    std::vector<int> _primes;
    for (int &p : primes)
        if (std::any_of(terms.begin(), terms.end(), [&p](int &t){ return t % p == 0; }))
            _primes.emplace_back(p);

    int count = 0;
    std::vector<mpq_class> results;
    search(terms, mpq_class(1, 2), _primes, results);
    for (mpq_class &result : results)
        if (std::find(valid_results.begin(), valid_results.end(), result) != valid_results.end())
            count++;

    std::cout << count;
}
