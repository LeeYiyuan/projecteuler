/*
    We scan the columns from left to right and for each row of the current column
    column, we determine the minimum possible sum terminating at that cell.

    Consider a path ending at A[r, c] with minimum sum M[r, c]. Then A[r, c]
    must be connected to some element in the column c - 1 either directly, in which
    case the path ends with

        A[r, c - 1] -> A[r, c]

    or indirectly, in which case there exists r' != r such that the path ends with

        A[r', c - 1] -> A[r', c] -> A[r' + 1, c] -> ... -> A[r, c] if r' < c, or
        A[r', c - 1] -> A[r', c] -> A[r' - 1, c] -> ... -> A[r, c] if r' > c

    We select the minimum M[r_min, c_min] of these possible previous paths and set
    M[r, c] = A[r, c] + M[r_min, c_min].
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "io_util.h"
#include "string_util.h"

int main()
{
    std::string matrix_string = read_file("082_matrix.txt");
    std::vector<std::vector<int>> A;
    std::vector<std::vector<int>> M;
    for (std::string &matrix_row_string : split(matrix_string, '\n'))
    {
        A.emplace_back();
        M.emplace_back();
        for (std::string &n_string : split(matrix_row_string, ','))
        {
            A.back().emplace_back(std::stoi(n_string));
            M.back().emplace_back(0);
        }
    }


    // Assumes A is a square matrix.
    for (int c = 0; c < A.size(); c++)
    {
        for (int r = 0; r < A.size(); r++)
        {
            if (c == 0)
            {
                M[r][c] = A[r][c];
            }
            else
            {
                std::vector<int> candidates = { M[r][c - 1] };
                for (int r_prime = 0; r_prime < A.size(); r_prime++)
                {
                    int candidate = M[r_prime][c - 1];
                    if (r_prime < r)
                    {
                        int _r_prime = r_prime;
                        while (_r_prime < r)
                        {
                            candidate += A[_r_prime][c];
                            _r_prime++;
                        }
                    }
                    else if (r_prime > r)
                    {
                        int _r_prime = r_prime;
                        while (_r_prime > r)
                        {
                            candidate += A[_r_prime][c];
                            _r_prime--;
                        }
                    }
                    candidates.emplace_back(candidate);
                }
                M[r][c] = A[r][c] + *std::min_element(candidates.begin(), candidates.end());
            }
        }
    }

    std::cout << std::min_element(M.begin(), M.end(),
        [](std::vector<int> const &r1, std::vector<int> const &r2){ return r1.back() < r2.back(); })->back();
}
