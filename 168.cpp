/*
    Observe that for a given number n, we can narrow down the next possible 
    digit d by selecting d such that there exists a and b for which

        10 * b * concat(n, d) <= concat(a, n, d) < 10 * b * concat(n, d)
    
    We use this fact and carry out DFS on the digits from left to right to
    find the required numbers and their sum.
*/

#include <iostream>
#include <vector>
#include <gmpxx.h>
#include "number_util.h"

void search(mpz_class n, int length, mpz_class &sum)
{
    if (length > 100)
        return;

    if (n % 10 != 0 && (n / 10 + (n % 10) * util::pow(mpz_class(10), length - 1)) % n == 0) 
        sum += n;
        
    for (mpz_class d = 0; d <= 9; d++)
    {
        mpz_class min = 10 * n + d;
        mpz_class max = 10 * n + (d + 1);

        mpz_class exp_length = util::pow(mpz_class(10), length);

        mpz_class m_min = min, m_max = max;
        
        bool found = false;
        for (; !found && m_min <= 10 * exp_length; m_min += min, m_max += max)
        {
            for (int i = 1; !found && i <= 9; i++)
            {
                mpz_class check = i * (exp_length * 10) + 10 * n + d;
                found = 10 * m_min <= check && check < 10 * m_max;
            }
        }
        if (found) search(10 * n + d, length + 1, sum);
    }
}

int main()
{
    mpz_class sum = 0;
    for (int n = 10; n <= 99; n++)
        search(n, 2, sum);
    std::cout << sum % 100000;
}