/*
    We are considering the concatenated product of an integer a with (1, 2, ..., n)
    with n > 1, i.e. n >= 2. If a >= 10000, then 2a >= 20000. As such, the
    concatenated product will have at least 10 digits. By the pigeonhole principle,
    one of the digit will occur at least twice, making it non pandigital.

    As such we only need consider a < 10000.

    Also since all valid products are exactly 9 digits long, we can compare the
    strings directly instead of having to convert them into a numerical.
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int main()
{
    std::string max_product_string = "000000000";
    std::vector<char> pandigital_digits = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    for (int a = 1; a < 10000; a++)
    {
        std::string product_string = "";
        int n = 1;
        while (product_string.length() < 8) // Extend to at least 9 digits long.
        {
            product_string += std::to_string(n * a);
            n++;
        }
        if (product_string.length() != 9) // If not possible to produce exactly 9 digits.
            continue;

        if (std::is_permutation(product_string.begin(), product_string.end(), pandigital_digits.begin()))
            max_product_string = std::max(max_product_string, product_string);
    }

    std::cout << max_product_string;
}
