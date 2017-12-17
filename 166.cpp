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


    d   [-1  -1   2   1   0   2   -1  0   1   0   0   0   1   0   0   0 ] + 
    a24 [ 1   1  -1  -1  -1  -1   1   1   0   0   0   0   0   0   0   0 ] + 
    a32 [ 0  -1   1   0   1   0  -1   0  -1   1   0   0   0   0   0   0 ] + 
    a33 [ 0   1  -1   0   1  -1   0   0  -1   0   1   0   0   0   0   0 ] +
    a34 [ 1   1  -1  -1   0  -1   1   0  -1   0   0   1   0   0   0   0 ] +
    a42 [ 1   0  -1   0   0  -1   1   0   0   0   0   0  -1   1   0   0 ] +
    a43 [ 1   1  -2   0   0  -1   1   0   0   0   0   0  -1   0   1   0 ] +
    a44 [ 1   2  -2  -1   0  -2   2   0   0   0   0   0  -1   0   0   1 ] +

    where a24, a32, a33, a34, a42, a43, a44 are arbitrary parameters.

    Finally, we iterate through d = 0, ..., 36 and then run DFS on the free
    parameters, at each level exploting some monotonic constraints between the
    free parameters to prune some branches.
*/

#include <iostream>
#include <vector>
#include <cmath>

bool verify(std::vector<int> const &values)
{
    for (int i = 0; i < values.size(); i++) 
        if (values[i] < 0 || values[i] > 9) 
            return false;
    return true;
}

int main()
{
    std::vector<std::vector<int>> bases = {
        { -1,  -1,   2,   1,   0,   2,  -1,   0,   1,   0,   0,   0,   1,   0,   0,   0  },
        {  1,   1,  -1,  -1,  -1,  -1,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0  },
        {  0,  -1,   1,   0,   1,   0,  -1,   0,  -1,   1,   0,   0,   0,   0,   0,   0  },
        {  0,   1,  -1,   0,   1,  -1,   0,   0,  -1,   0,   1,   0,   0,   0,   0,   0  },
        {  1,   1,  -1,  -1,   0,  -1,   1,   0,  -1,   0,   0,   1,   0,   0,   0,   0  },
        {  1,   0,  -1,   0,   0,  -1,   1,   0,   0,   0,   0,   0,  -1,   1,   0,   0  },
        {  1,   1,  -2,   0,   0,  -1,   1,   0,   0,   0,   0,   0,  -1,   0,   1,   0  },
        {  1,   2,  -2,  -1,   0,  -2,   2,   0,   0,   0,   0,   0,  -1,   0,   0,   1  }
    };

    int count = 0;
    std::vector<int> vector(16);
    for (int d = 0; d <= 36; d++)
    {
        for (int a24 = 0; a24 <= std::min(9, d); a24++)
            for (int a32 = 0; a32 <= std::min(9, d); a32++)
                for (int a33 = 0; a33 <= std::min(9, std::min(9 + a24 - a32, std::min(2 * d - a24, d - a32))); a33++)
                    for (int a34 = 0; a34 <= std::min(9, std::min(9 + d - a24 - a34, std::min(d - a24, std::min(2 * d - a24 - a33, d - a32 - a33)))); a34++)
                        for (int a42 = 0; a42 <= std::min(9, std::min(2 * d - a24 - a33 - a34, d)); a42++)
                            for (int a43 = 0; a43 <= std::min(9, std::min(2 * d - a24 - a33 - a34 - a42, d - a42)); a43++)
                                for (int a44 = 0; a44 <= std::min(9, std::min(9 + d - a24 - a34 - a42 - a43, std::min(d - a24 - a34, std::min((2 * d - a24 - a33 - a34 - a42 - a43) / 2, d - a42 - a43)))); a44++, count += verify(vector))
                                    for (int i = 0; i < 16; i++)
                                        vector[i] = 
                                            d   * bases[0][i] + 
                                            a24 * bases[1][i] + 
                                            a32 * bases[2][i] +
                                            a33 * bases[3][i] +
                                            a34 * bases[4][i] +
                                            a42 * bases[5][i] +
                                            a43 * bases[6][i] +
                                            a44 * bases[7][i];
    }

    std::cout << count << std::endl;
}