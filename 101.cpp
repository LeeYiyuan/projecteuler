/*
    Essentially, for

        u(n) = 1 - n + n^2 - ... + n^10
             = (n^11 + 1) / (n + 1)

    we look for the interpolating polynomial p_1, p_2, ..., p_10 for the first
    1, 2, ..., 10 terms of u_n.

    For each interpolating polynomial p_i we find the first value of n such that
    p_i(n) != u(n). The values p_i(n) are collected and summed to give the required
    result.

    For interpolation, we use Lagrange's Interpolation. The idea is that we explictly
    construct terms for each value in the set of interpolating points. Every term
    will be "annihilated" except when n equals to the x value of the point
    corresponding to the term. For example to interpolating (1, 1), (2, 8), (3, 15),
    we have

        p(n) = 1 * (n - 8)(n - 15) / ((1 - 8)(1 - 15)) +
               8 * (n - 1)(n - 15) / ((2 - 1)(2 - 15))
               15 * (n - 1)(n - 2) / ((3 - 1)(3 - 2))

    Indeed, for each term, when n is not equal to the corresponding x value, the
    numerator is "annihilated" and the term becomes zero. If n is equal to the
    corresponding x value, the denominator is constructed to cancel out the
    numerator to give 1, which is multiplied by the y value of the point.
*/

#include <iostream>
#include <vector>
#include <gmpxx.h>
#include "number_util.h"

struct term_struct
{
    mpz_class value;
    std::vector<int> offsets;
    mpz_class denominator = 1;
};

std::vector<term_struct> interpolate(std::vector<mpz_class> values)
{
    std::vector<term_struct> terms;

    for (int n = 0; n < values.size(); n++)
    {
        mpz_class value = values[n];

        terms.emplace_back();
        term_struct &term = terms.back();
        term.value = value;
        for (int _n = 0; _n < values.size(); _n++)
        {
            if (_n != n)
            {
                term.offsets.emplace_back(_n + 1);
                term.denominator *= n - _n;
            }
        }
    }

    return terms;
}

mpz_class evaluate(std::vector<term_struct> terms, int n)
{
    mpz_class s = 0;
    for (term_struct &term : terms)
    {
        mpz_class _s = term.value;
        for (int &offset : term.offsets)
            _s *= n - offset;
        _s /= term.denominator;
        s += _s;
    }
    return s;
}

mpz_class evaluate_U(int n)
{
    return (util::pow(n, 11) + 1) / (n + 1);
}

int main()
{
    mpz_class s = 0;
    for (int k = 1; k < 11; k++)
    {
        std::vector<mpz_class> values;
        for (int n = 1; n <= k; n++)
            values.emplace_back(evaluate_U(n));

        std::vector<term_struct> polynomial = interpolate(values);

        int n = 0;
        mpz_class p_n;
        do {
            n++;
            p_n = evaluate(polynomial, n);
        } while(p_n == values[n - 1]);
        s += p_n;
    }

    std::cout << s;
}
