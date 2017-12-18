/*
    First, assign the cells in the grid to columns in a 10 X 16 matrix, where
    the assignment goes left to right, followed by top to bottom. The top left
    cell corresponds to the first column, and the bottom right cell corresponds
    to the last column.

    Let the common sum be d. Each row represents a constraint - elements in the
    row with 1 is constrained to have the the same sum. There are 10 rows
    because of the constraints existing on the 4 rows, 4 columns and 2 main
    diagonals.

    Note that we can represent the entire problem as finding solution vectors
    in \mathbb{Z}^16, where each element is a digit, to the corresponding 
    augmented matrix

        1   1   1   1   0   0   0   0   0   0   0   0   0   0   0   0   | d
        0   0   0   0   1   1   1   1   0   0   0   0   0   0   0   0   | d
        0   0   0   0   0   0   0   0   1   1   1   1   0   0   0   0   | d
        0   0   0   0   0   0   0   0   0   0   0   0   1   1   1   1   | d
        1   0   0   0   1   0   0   0   1   0   0   0   1   0   0   0   | d
        0   1   0   0   0   1   0   0   0   1   0   0   0   1   0   0   | d
        0   0   1   0   0   0   1   0   0   0   1   0   0   0   1   0   | d
        0   0   0   1   0   0   0   1   0   0   0   1   0   0   0   1   | d
        1   0   0   0   0   1   0   0   0   0   1   0   0   0   0   1   | d
        0   0   0   1   0   0   1   0   0   1   0   0   1   0   0   0   | d

    for which the RREF, using MATLAB, is

        1   0   0   0   0   0   0  -1   0   0   0  -1   0  -1  -1  -1   |  -d
        0   1   0   0   0   0   0  -1   0   1  -1  -1   0   0  -1  -2   |  -d
        0   0   1   0   0   0   0   1   0  -1   1   1   0   1   2   2   | 2*d
        0   0   0   1   0   0   0   1   0   0   0   1   0   0   0   1   |   d
        0   0   0   0   1   0   0   1   0  -1  -1   0   0   0   0   0   |   0
        0   0   0   0   0   1   0   1   0   0   1   1   0   1   1   2   | 2*d
        0   0   0   0   0   0   1  -1   0   1   0  -1   0  -1  -1  -2   |  -d
        0   0   0   0   0   0   0   0   1   1   1   1   0   0   0   0   |   d
        0   0   0   0   0   0   0   0   0   0   0   0   1   1   1   1   |   d
        0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   |   0

    Solving as usual, we get solutions

        d[-1  -1   2   1   0   2   -1  0   1   0   0   0   1   0   0   0 ] + v

    where v is in the span of the vectors

        [ 1   1  -1  -1  -1  -1   1   1   0   0   0   0   0   0   0   0 ],
        [ 0  -1   1   0   1   0  -1   0  -1   1   0   0   0   0   0   0 ], 
        [ 0   1  -1   0   1  -1   0   0  -1   0   1   0   0   0   0   0 ],
        [ 1   1  -1  -1   0  -1   1   0  -1   0   0   1   0   0   0   0 ],
        [ 1   0  -1   0   0  -1   1   0   0   0   0   0  -1   1   0   0 ],
        [ 1   1  -2   0   0  -1   1   0   0   0   0   0  -1   0   1   0 ],
        [ 1   2  -2  -1   0  -2   2   0   0   0   0   0  -1   0   0   1 ]
    
    which also has basis, considering the RREF of the appropriate matrix, 

        [ 1   0   0  -1   0   0   0   0   0   2  -2   0  -1  -2   2   1 ],
        [ 0   1   0  -1   0   0   0   0   0   1  -1   0   0  -2   1   1 ],
        [ 0   0   1  -1   0   0   0   0   0   1  -1   0   0  -1   0   1 ],
        [ 0   0   0   0   1   0   0  -1   0   1  -1   0  -1  -1   1   1 ],
        [ 0   0   0   0   0   1   0  -1   0   0  -1   1   0  -1   1   0 ],
        [ 0   0   0   0   0   0   1  -1   0  -1   0   1   0   1  -1   0 ],
        [ 0   0   0   0   0   0   0   0   1   1  -1  -1  -1  -1   1   1 ]

    We loop through each possible value of d from d = 36. For each d, we do
    DFS search for v using the above basis for the span that v must exist in.

    The nice thing about the form of the above basis is that for each vector,
    we can easily consider the elements from the current pivot entry to the
    entry in the column just before the next pivot column to impose a bound
    on the current coordinate. 
    
    Additionally, all the entries from any one pivot entry to the element in
    the same row just before the next pivot column (or the end of the matrix)
    is either 1 or -1 which removes the need for any division, which makes 
    things easier when calculating the required bounds.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

bool verify(std::vector<int> const &values)
{
    for (int i = 0; i < values.size(); i++) 
      if (values[i] < 0 || values[i] > 9) 
        return false;
    return true;
}

void search(std::vector<std::vector<int>> const &basis, std::vector<int> const &pivot_columns, int index, std::vector<int> const &vector, int &count)
{
    int start = INT_MIN, end = INT_MAX;

    for (int i = pivot_columns[index]; i < (index < pivot_columns.size() - 1 ? pivot_columns[index + 1] : vector.size()); i++)
    {
        if (basis[index][i] == 1)
        {
            start = std::max(start, -vector[i]);
            end = std::min(end, 9 - vector[i]);
        }
        else if (basis[index][i] == -1)
        {
            start = std::max(start, vector[i] - 9);
            end = std::min(end, vector[i]);
        }
    }

    if (end < start) return;
    if (index == basis.size() - 1) { count += end - start + 1; return; }

    std::vector<int> _vector(vector.size());
    for (int i = start; i <= end; i++)
    {
        for (int j = 0; j < _vector.size(); j++)
            _vector[j] = vector[j] + i * basis[index][j];
        search(basis, pivot_columns, index + 1, _vector, count);
    }
}

int main()
{
    std::vector<int> d_vector = { -1, -1, 2, 1, 0, 2, -1, 0, 1, 0, 0, 0, 1, 0, 0, 0 };
    std::vector<std::vector<int>> basis = {
        { 1,  0,  0, -1,  0,  0,  0,  0,  0,  2, -2,  0, -1, -2,  2, 1 },
        { 0,  1,  0, -1,  0,  0,  0,  0,  0,  1, -1,  0,  0, -2,  1, 1 },
        { 0,  0,  1, -1,  0,  0,  0,  0,  0,  1, -1,  0,  0, -1,  0, 1 },
        { 0,  0,  0,  0,  1,  0,  0, -1,  0,  1, -1,  0, -1, -1,  1, 1 },
        { 0,  0,  0,  0,  0,  1,  0, -1,  0,  0, -1,  1,  0, -1,  1, 0 },
        { 0,  0,  0,  0,  0,  0,  1, -1,  0, -1,  0,  1,  0,  1, -1, 0 },
        { 0,  0,  0,  0,  0,  0,  0,  0,  1,  1, -1, -1, -1, -1,  1, 1 }
    };
    std::vector<int> pivot_columns = { 0, 1, 2, 4, 5, 6, 8 };

    int count = 0;
    std::vector<int> vector(16);
    for (int d = 0; d <= 36; d++)
    {
        search(basis, pivot_columns, 0, vector, count);
        for (int i = 0; i < vector.size(); i++)
            vector[i] += d_vector[i];
    }

    std::cout << count << std::endl;
}