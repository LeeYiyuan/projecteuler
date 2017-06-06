#include <gmpxx.h>
#include <iostream>
#include <string>
#include <algorithm>
#include "string_util.h"

int main()
{
    int count = 0;
    for (int n = 10; n < 10000; n++)
    {
        mpz_class _n = n;
        bool is_hit = true;
        for (int i = 0; i < 50; i++)
        {
            std::string _n_string = _n.get_str();
            std::reverse(_n_string.begin(), _n_string.end());

            // GMP can't handle leading zeroes when parsing integer strings.
            // This is quite inefficient but I was too lazy to write anything more.
            while (_n_string[0] == '0') _n_string = _n_string.substr(1, _n_string.length() - 1);

            _n += mpz_class(_n_string);

            if (util::is_palindrome(_n.get_str()))
            {
                is_hit = false;
                break;
            }
        }
        if (is_hit)
            count++;
    }

    std::cout << count;
}
