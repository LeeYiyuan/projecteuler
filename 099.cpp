/*
    We know that for a, b > 1, since log is a strictly increasing function,

        a > b iff log(a) > log(b)

    so instead we track values of log(base ^ exponent) = exponent * log(base)
    and see which line number gives the largest value.
*/

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "io_util.h"
#include "string_util.h"

int main()
{
    std::string pairs_string = util::read_file("099_base_exp.txt");
    std::vector<std::pair<int, int>> pairs;
    for (std::string &pair_string : util::split(pairs_string, '\n'))
    {
        std::vector<std::string> splitted = util::split(pair_string, ',');
        pairs.emplace_back(std::stoi(splitted[0]), std::stoi(splitted[1]));
    }

    double value_best = -1;
    int i_best;
    for (int i = 0; i < pairs.size(); i++)
    {
        std::pair<int, int> &pair = pairs[i];
        double value = pair.second * std::log2(pair.first);
        if (value > value_best)
        {
            value_best = value;
            i_best = i;
        }
    }

    // Convert 0-based to 1-based index.
    std::cout << i_best + 1;
}
