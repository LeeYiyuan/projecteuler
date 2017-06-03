/*
    Consider a * b = n.
    Let k_a, k_b, k_n be the number of digits of a, b, n respectively.
    Then

        10^{k_a - 1} <= a <= 10^{k_a}
        10^{k_b - 1} <= b <= 10^{k_b}
        10^{k_a + k_b - 2} <= ab <= 10^{k_a + k_b}

    This means that given k_a and k_b, we have

        k_a + k_b - 1 <= k_n <= k_a + k_b

    We need k_a + k_b + k_n = 9. That is,

        2k_a + 2k_b >= 9, 2k_a + 2k_b <= 10
        4.5 <= k_a + k_b <= 5
        4.5 - k_a <= k_b <= 5 - k_a

    Since k_a is an integer,

        k_b = 5 - k_a
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

int main()
{
    int sum = 0;
    std::vector<int> hits;

    for (int a_digits = 1; a_digits < 5; a_digits++)
    {
        int b_digits = 5 - a_digits;
        for (int a = (int)std::pow(10, a_digits - 1); a < int(std::pow(10, a_digits)); a++)
        {
            for (int b = (int)std::pow(10, b_digits - 1); b < int(std::pow(10, b_digits)); b++)
            {
                int n = a * b;
                std::string digits = std::to_string(a) + std::to_string(b) + std::to_string(n);
                if (digits.length() == 9)
                {
                    std::sort(digits.begin(), digits.end());
                    if (std::adjacent_find(digits.begin(), digits.end()) == digits.end() && std::find(digits.begin(), digits.end(), '0') == digits.end())
                    {
                        if (std::find(hits.begin(), hits.end(), n) == hits.end())
                        {
                            sum += n;
                            hits.emplace_back(n);
                        }
                    }
                }
            }
        }
    }

    std::cout << sum;
}
