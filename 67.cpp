/*
    We use dynamic programming : From bottom up, the maximum possible path sum
    starting at a particular node and ending all the way at the bottom is saved
    in memory.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "io_util.h"
#include "string_util.h"

int main()
{
    std::string triangle_string = read_file("67_triangle.txt");
    std::vector<std::vector<int>> triangle;
    for (std::string &triangle_row_string : split(triangle_string, '\n'))
    {
        triangle.emplace_back();
        for(std::string &number_string : split(triangle_row_string, ' '))
        {
            triangle.back().emplace_back(std::stoi(number_string));
        }
    }
    std::reverse(triangle.begin(), triangle.end());

    std::vector<std::vector<int>> maximal_sub_sums;

    for (int r = 0; r < triangle.size(); r++)
    {
        maximal_sub_sums.emplace_back();
        for (int c = 0; c < triangle[r].size(); c++)
        {
            maximal_sub_sums[r].emplace_back(
                r == 0 ? triangle[r][c]:
                triangle[r][c] + std::max(maximal_sub_sums[r - 1][c], maximal_sub_sums[r - 1][c + 1]));
        }
    }

    std::cout << maximal_sub_sums.back().back();
}
