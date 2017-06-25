/*
    First we generate the list of figurate numbers with 4 digits.

    We know that every list of cyclic numbers can be rearranged by shifting the
    last element to the first. As such, we can decide on a figure number to
    start our search. In this case, I've decided to start with the triangular
    number.

    Recursively, we run through the figures not picked yet and for each unpicked
    figure, we select the numbers of that figure whose 2 leading digits are the
    same as the 2 trailing digits of the previously selected number from the
    previous figure. We then do a recursive call to the next step.

    Termination occurs when all a number has been picked from all figures.
*/

#include <functional>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

std::vector<std::vector<int>> numbers;
std::vector<std::map<int, std::vector<int>>> numbers_map;
std::vector<std::function<int(int)>> formulas =
{
    [](int n){ return n * (n + 1) / 2; },
    [](int n){ return n * n; },
    [](int n){ return n * (3 * n - 1) / 2; },
    [](int n){ return n * (2 * n - 1); },
    [](int n){ return n * (5 * n - 3) / 2; },
    [](int n){ return n * (3 * n - 2); }
};

int recurse(std::vector<int> const &selected_numbers, std::vector<int> const &remaining_figure_indexes)
{
    if (remaining_figure_indexes.size() == 0)
    {
        if (selected_numbers.back() % 100 == selected_numbers[0] / 100)
        {
            int sum = 0;
            for (int const &n : selected_numbers)
                sum += n;
            return sum;
        }
        return -1;
    }

    int trailing_digits = selected_numbers.back() % 100;
    for (int const &figure_index : remaining_figure_indexes)
    {
        if (numbers_map[figure_index].find(trailing_digits) != numbers_map[figure_index].end())
        {
            std::vector<int> _remaining_figure_indexes(remaining_figure_indexes.size() - 1);
            std::copy_if(
                remaining_figure_indexes.begin(),
                remaining_figure_indexes.end(),
                _remaining_figure_indexes.begin(),
                [figure_index](int i){ return i != figure_index; });
            for (int &number : numbers_map[figure_index][trailing_digits])
            {
                std::vector<int> _selected_numbers(selected_numbers);
                _selected_numbers.emplace_back(number);
                int result = recurse(_selected_numbers, _remaining_figure_indexes);
                if (result != -1)
                    return result;
            }
        }
    }

    return -1;
}

int main()
{
    for (std::function<int(int)> &f : formulas)
    {
        numbers.emplace_back();
        numbers_map.emplace_back();
        int n = 0;
        int p_n;
        while ((p_n = f(++n)) < 10000)
        {
            if (p_n >= 1000)
            {
                numbers.back().emplace_back(p_n);
                int leading_digits = p_n / 100;
                if (numbers_map.back().find(leading_digits) == numbers_map.back().end())
                    numbers_map.back().emplace(leading_digits, std::vector<int>{});
                numbers_map.back()[leading_digits].emplace_back(p_n);
            }
        }
    }

    for (int &number : numbers[0])
    {
        std::vector<int> selected_numbers = { number };
        std::vector<int> remaining_figure_indexes = { 1, 2, 3, 4, 5 };
        int result = recurse(selected_numbers, remaining_figure_indexes);
        if (result != -1)
        {
            std::cout << result;
            return 0;
        }
    }
}
