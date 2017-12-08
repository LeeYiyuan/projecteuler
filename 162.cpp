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
    
    and we simply sum the values of |A & B & C| across d = 3, ..., 16.
*/

#include <iostream>
#include <number_util.h>
#include <gmpxx.h>
#include <cctype>

int main()
{
    mpz_class count = 0;
    for (int d = 3; d <= 16; d++)
        count += 15 * util::pow(16, d - 1) - util::pow(13, d) + 41 * util::pow(14, d - 1) - 43 * util::pow(15, d - 1);
    
    std::string result = count.get_str(16);
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);

    std::cout << result;
}