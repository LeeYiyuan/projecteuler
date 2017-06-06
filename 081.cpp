/*
    For each element, we determine the minimum possible sum ending at that element.
    This can be done by adding it with the minimum of the two previous elements,
    giving us the recurrence relation for the minimum sum ending at the element:
    at row r and column c:

        M(r, c) = matrix[r][c] + min(M(r, c - 1), M(r - 1, c))
        M(r, c) = 0 for r < 0 or c < 0

    We need to find M(80, 80). However in this recursion, there exists elements
    that are visited more than once. For example, M(70, 71) and M(70, 71) both
    considers M(70, 70), leading to unnecessary evaluations.

    As such, we use dynamic programming. We start from the top row and move left
    to right, computing the minimums and storing them once. We move downwards
    to the other rows with the same steps.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "io_util.h"
#include "string_util.h"

int main()
{
    std::string matrix_string = util::read_file("081_matrix.txt");
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<int>> M;
    for (std::string &matrix_row_string : util::split(matrix_string, '\n'))
    {
        matrix.emplace_back();
        M.emplace_back();
        for (std::string &n_string : util::split(matrix_row_string, ','))
        {
            matrix.back().emplace_back(std::stoi(n_string));
            M.back().emplace_back(0);
        }
    }

    for (int r = 0; r < matrix.size(); r++)
    {
        for (int c = 0; c < matrix[r].size(); c++)
        {
            int e = matrix[r][c];
            if (r > 0 && c > 0)
                e += std::min(M[r - 1][c], M[r][c - 1]);
            else if (r > 0)
                e += M[r - 1][c];
            else if (c > 0)
                e += M[r][c - 1];
            M[r][c] = e;
        }
    }

    std::cout << M.back().back();
}
