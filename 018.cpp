/*
    We use dynamic programming : From bottom up, the maximum possible path sum
    starting at a particular node and ending all the way at the bottom is saved
    in memory.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include "string_util.h"

int main()
{
    std::string triangle_string =
R"(75
95 64
17 47 82
18 35 87 10
20 04 82 47 65
19 01 23 75 03 34
88 02 77 73 07 63 67
99 65 04 28 06 16 70 92
41 41 26 56 83 40 80 70 33
41 48 72 33 47 32 37 16 94 29
53 71 44 65 25 43 91 52 97 51 14
70 11 33 28 77 73 17 78 39 68 17 57
91 71 52 38 17 14 91 43 58 50 27 29 48
63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23)";

    std::vector<std::string> triangle_row_strings = util::split(triangle_string, '\n');
    std::reverse(triangle_row_strings.begin(), triangle_row_strings.end());

    std::vector<std::vector<int>> triangle;
    for (std::string &triangle_row_string : triangle_row_strings)
    {
        triangle.emplace_back();
        for (std::string &number : util::split(triangle_row_string, ' '))
            triangle.back().emplace_back(std::stoi(number));
    }

    std::vector<std::vector<int>> max_sub_sums;
    for (std::vector<int> &triangle_row : triangle)
    {
        max_sub_sums.emplace_back();
        for (int &number : triangle_row)
            max_sub_sums.back().emplace_back(0);
    }

    for (int r = 0; r < triangle.size(); r++)
        for (int c = 0; c < triangle[r].size(); c++)
            max_sub_sums[r][c] = r == 0 ? triangle[r][c] : triangle[r][c] + std::max(max_sub_sums[r - 1][c], max_sub_sums[r - 1][c + 1]);

    std::cout << max_sub_sums.back().back();
}
