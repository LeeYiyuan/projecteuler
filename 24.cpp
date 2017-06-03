/*
    Consider the first permutation that starts with digit k where 0 < k <= 9.
    There are permutations that lie before it starting with digits 0, 1, ..., k - 1.
    In each case, we can count this by selecting the first digit, and then
    considering the number of ways to permute the remaining 9 digits. There
    are 9! cases for a total of k * 9! cases.

    The same argument can be extended to the following digits to find the permutation
    with 1000000 - 1 permutations preceding it. This number is then the 1000000th
    permutation.
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> available_digits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<int> digits;
    int n_permutations = 0;

    int fact = 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1;
    while (!available_digits.empty())
    {
        fact /= available_digits.size();
        int digit_index = (999999 - n_permutations) / fact;
        int digit = available_digits[digit_index];
        digits.emplace_back(digit);
        available_digits.erase(
            std::remove(available_digits.begin(), available_digits.end(), digit),
            available_digits.end());
        n_permutations += digit_index * fact;
    }

    std::string number_string = "";
    for (int &digit : digits)
        number_string += '0' + (char)digit;

    std::cout << number_string;
}
