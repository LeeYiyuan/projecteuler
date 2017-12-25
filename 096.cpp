/*
    This problem can be solved by direct application of backtrack search.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "io_util.h"
#include "string_util.h"

typedef std::vector<std::vector<int>> grid_t;

bool is_valid(grid_t const &grid, int r, int c)
{
    // Check row.
    for (int _c = 0; _c < 9; _c++)
        if (_c != c && grid[r][_c] != 0 && grid[r][c] == grid[r][_c])
            return false;

    // Check column.
    for (int _r = 0; _r < 9; _r++)
        if (_r != r && grid[_r][c] != 0 && grid[r][c] == grid[_r][c])
            return false;

    // Check square.
    for (int _r = 3 * (r / 3); _r < 3 * (r / 3) + 3; _r++)
        for (int _c = 3 * (c / 3); _c < 3 * (c / 3) + 3; _c++)
            if (_r != r && _c != c && grid[_r][_c] != 0 && grid[_r][_c] == grid[r][c])
                return false;

    return true;
}

bool solve(grid_t &grid, int r, int c)
{
    if (r == 9)
        return true;

    bool is_set = grid[r][c] != 0;
    std::vector<int> digits = is_set ? std::vector<int>{ grid[r][c] } : std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (int &digit : digits)
    {
        grid[r][c] = digit;
        if (is_valid(grid, r, c))
        {
            int _r = r;
            int _c = c + 1;
            if (_c > 8)
            {
                _r++;
                _c = 0;
            }
            if (solve(grid, _r, _c))
                return true;
        }
    }

    // Reset.
    if (!is_set)
        grid[r][c] = 0;

    return false;
}

int main()
{
    std::string grid_string = util::read_file("096_sudoku.txt");
    std::vector<std::string> grid_row_strings = util::split(grid_string, '\n');
    std::vector<grid_t> grid;

    for (int i = 0; i < 50; i++)
    {
        grid.emplace_back(9, std::vector<int>(9));
        for (int r = 0; r < 9; r++)
            for (int c = 0; c < 10; c++)
                grid.back()[r][c] = grid_row_strings[i * 10 + r + 1][c] - '0';
    }

    int s = 0;
    for (grid_t &grid : grid)
    {
        solve(grid, 0, 0);
        s += grid[0][0] * 100 + grid[0][1] * 10 + grid[0][2];
    }

    std::cout << s;
}
