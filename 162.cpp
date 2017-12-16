/*
    For each number of digits d, let 
    
        A be the set of d digit numbers that include at least one '0', 
        B be the set of d digit numbers that include at least one '1',
        C be the set of d digit numbers that include at least one 'A'

    Then using the Principle of Inclusion-Exclusion and considering what the
    first digit can and connot be, we get

        |A & B & C| = |A | B | C| - |A | B| - |A | C| - |B | C| + |A| + |B| + |C|
                    =   (15 * 16^{d - 1} - 13^d) 
                      - (15 * 16^{d - 1} - 14^d) 
                      - (15 * 16^{d - 1} - 14^d) 
                      - (15 * 16^{d - 1} - 13 * 14^{d - 1}) 
                      + (15 * 16^{d - 1} - 15^d) 
                      + (15 * 16^{d - 1} - 14 * 15^{d - 1}) 
                      + (15 * 16^{d - 1} - 14 * 15^{d - 1})
                    = 15 * 16^{d - 1} - 13^d + 41 * 14^{d - 1} - 43 * 15^{d - 1}
    
    and we simply sum the values of |A & B & C| across d = 3, ..., 16. We use
    the formula for the sum of a geometric series to obtain a closed form,

        |A & B & C| = 15 * (16^n - 16^2) / (16 - 1) - 
                      (13^{n + 1} - 13^3) / (13 - 1) +
                      41 * (14^n - 14^2) / (14 - 1) -
                      43 * (15^n - 15^2) / (15 - 1)
    
    where n is the number of digits in the string.
*/

#include <iostream>
#include <number_util.h>
#include <gmpxx.h>
#include <cctype>

int main()
{
    int n = 16;

    mpz_class count = 
        15 * (util::pow(16, n) - util::pow(16, 2)) / (16 - 1) -
        (util::pow(13, n + 1) - util::pow(13, 3)) / (13 - 1) +
        41 * (util::pow(14, n) - util::pow(14, 2)) / (14 - 1) -
        43 * (util::pow(15, n) - util::pow(15, 2)) / (15 - 1);
    
    std::string result = count.get_str(16);
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);

    std::cout << result;
}