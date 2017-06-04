/*
    We group parts of the decimal digits according to their number of digits:
        k = 1 : 1, 2, ..., 9,         -> 1 * (9 - 1 + 1) digits total.
        k = 2 : 10, 11, ..., 99,      -> 2 * (99 - 10 + 1) digits total.
        k = 3 : 100, 101, ..., 999,   -> 3 * (999 - 100 + 1) digits total.
        etc.

    We look for the group that contains d_n. Afterwards, we look for the item in
    that group that contains d_n. Finally, we look for the digit of that item that
    contains the d_n.
*/

#include <iostream>
#include <cmath>

int get_digit(int n)
{
    // 1-based group index.
    int k = 1;
    int n_group_digits = 9;
    while (n > n_group_digits)
    {
        n -= n_group_digits;
        k++;
        n_group_digits =  int(k * ((std::pow(10, k) - 1) - std::pow(10, k - 1) + 1));
    }

    // 1-based index of term.
    int index = int(std::ceil(n * 1.0 / k));

    // 1-based digit number of term.
    int digit_number = ((n - 1) % k) + 1;

    int term = int(std::pow(10, k - 1) - 1 + index);

    return std::to_string(term)[digit_number - 1] - '0';
}

int main()
{
    int product = 1;
    for (int exponent = 0; exponent < 7; exponent++)
        product *= get_digit(int(std::pow(10, exponent)));

    std::cout << product;
}
