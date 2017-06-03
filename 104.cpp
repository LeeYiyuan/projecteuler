/*
    Naive solution. Here we do the last digits check first because it is faster -
    we are only converting n modulo 10^9 to string as compared to converting
    the whole n to string in the first digtis check.
*/

#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <gmpxx.h>

std::vector<char> pandigital_digits =  { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

bool is_last_digits_pandigital(mpz_class n, int length)
{
    mpz_class r = n % 1000000000;
    std::string last_string = r.get_str();

    return std::is_permutation(last_string.begin(), last_string.end(), pandigital_digits.begin());
}

bool is_first_digits_pandigital(mpz_class n, int length)
{
    std::string n_string = n.get_str();
    std::string first_string = n_string.substr(
        0,
        std::min((int)n_string.length(), length)
    );

    return first_string.length() == pandigital_digits.size() &&
        std::is_permutation(first_string.begin(), first_string.end(), pandigital_digits.begin());
}

int main()
{
    mpz_class fn2 = 1;
    mpz_class fn1 = 1;
    int n = 2;
    while (true)
    {
        mpz_class _fn2 = fn1;
        mpz_class _fn1 = fn1 + fn2;
        fn2 = _fn2;
        fn1 = _fn1;
        n++;
        if (is_last_digits_pandigital(fn1, 9) && is_first_digits_pandigital(fn1, 9))
            break;
    }
    std::cout << n;
}
