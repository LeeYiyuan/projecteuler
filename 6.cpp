#include <iostream>

int main()
{
    int n = 100;

    // Faulhaber's formulas for sum of squares of first n natural numbers
    int sum_square = n * (n + 1) * (2 * n + 1) / 6;

    // Faulhaber's formulas for sum of first n natural numbers
    int sum = n * (n + 1) / 2;

    std::cout << sum * sum - sum_square;
}
