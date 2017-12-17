/*
    We start by selecting pairs of (d_2, d_3).

    For each pair, we select possible d_4 given by the requirement
    2 | 100d_2 + 10 d_3 + d_4. Equivalently, we need d_4 with remainder
    -100d_2 -10d_3 modulo 2.

    For each d_3 and d_4, we select possible d_5 given by the requirement
    3 | 100d_3 + 10d_4 + d_5. Equivalently, we need d_5 with remainder
    -100d_3 - 10d_4 modulo 3.

    We continue recursively until we have selected d_10.

    Afterwards, we select d_1 from the list of digits remaining.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdint>

std::vector<int> modulos = { 2, 3, 5, 7, 11, 13, 17 };

// Selects d_{index + 4} given the previously selected digits, starting with
// index = 0 => d_{index + 4} = d_4.
void process(int index, std::vector<int> const &numbers, std::vector<int> const &selected_numbers, std::vector<ull> &results)
{
    if (index == 7) // d_10 has been selected in previous recursion.
    {
        for (int const &number : numbers)
        {
            uint64_t s = 0;
            for (int i = 0; i < numbers.size(); i++)
                s += (ull)(std::pow(10, 10 - i - 1) * numbers[i]);
            for (int j = 0; j < selected_numbers.size(); j++)
                s += (ull)(std::pow(10, 10 - (numbers.size() + j) - 1) * selected_numbers[j]);
            results.emplace_back(s);
        }
        return;
    }

    int prev_sum = 100 * selected_numbers[index] + 10 * selected_numbers[index + 1];
    int modulo = modulos[index];
    for (int const &number : numbers)
    {
        if ((number + prev_sum) % modulo == 0)
        {
            std::vector<int> _numbers = numbers;
            _numbers.erase(std::remove(_numbers.begin(), _numbers.end(), number), _numbers.end());

            std::vector<int> _selected_numbers = selected_numbers;
            _selected_numbers.emplace_back(number);

            process(index + 1, _numbers, _selected_numbers, results);
        }
    }

}

int main()
{
    std::vector<int> numbers = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<ull> results;
    for (int &a : numbers)
    {
        for (int &b : numbers)
        {
            if (a != b)
            {
                std::vector<int> _numbers = numbers;
                _numbers.erase(std::remove(_numbers.begin(), _numbers.end(), a), _numbers.end());
                _numbers.erase(std::remove(_numbers.begin(), _numbers.end(), b), _numbers.end());

                std::vector<int> _selected_numbers = { a, b };

                process(0, _numbers, _selected_numbers, results);
            }
        }
    }

    uint64_t sum = 0;
    for (uint64_t &result : results)
        sum += result;

    std::cout << sum;
}
