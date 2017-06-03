/*
    Let n be such a number and let k the number of digtis in n.
    Then n is at most k * 9!. So we only need to check n for which

        n <= (\floor\lg n + 1) * 9!
*/

#include <cmath>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> factorials = { 1 };
    for (int i = 1; i < 10; i++)
        factorials.emplace_back(factorials.back() * i);

    int sum = 0;
    int n = 0;
    while (++n <= int(std::log10(n) + 1) * factorials[9])
    {
        int _n = n;
        int s = 0;
        while (_n > 0)
        {
            s += factorials[_n % 10];
            _n /= 10;
        }
        if (s == n && n != 1 && n != 2)
            sum += n;
    }

    std::cout << sum;
}
