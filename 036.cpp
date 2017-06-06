#include <iostream>
#include <string>
#include <algorithm>
#include "string_util.h"

std::string to_bit_string(int n)
{
    std::string s = "";
    while (n > 0)
    {
        s = (n & 1 ? '1' : '0') + s;
        n >>= 1;
    }
    return s;
}

int main()
{
    int sum = 0;

    // 1, 2, digit palindromes.
    for (int a = 1; a < 10; a++)
    {
        int n_1 = a;
        int n_2 = 10 * a + a;
        if (util::is_palindrome(to_bit_string(n_1))) sum += n_1;
        if (util::is_palindrome(to_bit_string(n_2))) sum += n_2;
    }

    // 3, 4 digit palindromes.
    for (int a = 1; a < 10; a++)
    {
        for(int b = 0; b < 10; b++)
        {
            int n_3 = 100 * a + 10 * b + a;
            int n_4 = 1000 * a + 100 * b + 10 * b + a;
            if (util::is_palindrome(to_bit_string(n_3))) sum += n_3;
            if (util::is_palindrome(to_bit_string(n_4))) sum += n_4;
        }
    }

    // 5, 6 digit palindromes.
    for (int a = 1; a < 10; a++)
    {
        for (int b = 0; b < 10; b++)
        {
            for (int c = 0; c < 10; c++)
            {
                int n_5 = 10000 * a + 1000 * b + 100 * c + 10 * b + a;
                int n_6 = 100000 * a + 10000 * b + 1000 * c + 100 * c + 10 * b + a;
                if (util::is_palindrome(to_bit_string(n_5))) sum += n_5;
                if (util::is_palindrome(to_bit_string(n_6))) sum += n_6;
            }
        }
    }

    std::cout << sum;
}
