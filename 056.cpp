#include <gmpxx.h>
#include <string>
#include <iostream>
#include <algorithm>
#include "number_util.h"

int main()
{
    int max_sum = -1;
    for (int a = 1; a < 100; a++)
    {
        for (int b = 0; b < 100; b++) // Exponent can be zero for a^b to be natural (a^0 = 1).
        {
            mpz_class v = util::pow(a, b);

            std::string v_string = v.get_str();
            int s = 0;
            for (char &c : v_string)
                s += c - '0';

            max_sum = std::max(max_sum, s);
        }
    }

    std::cout << max_sum;
}
