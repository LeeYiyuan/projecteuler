/*
    We use the recursive Binomial formula to generate Pascal's triangle. If any
    one of the relevant element in the previous row is greater than a million,
    we mark the current element with a marker to indicate that it is also greater
    than a million.

    Finally we count the total number of elements marked greater than a million.
*/

#include <iostream>
#include <vector>

int main()
{
    std::vector<std::vector<int>> triangle = { { 1 } };

    int count = 0;
    for (int i_r = 1; i_r <= 100; i_r++)
    {
        triangle.emplace_back(i_r + 1);
        std::vector<int> &row = triangle.back();
        for (int i_c = 0; i_c < i_r + 1; i_c++)
        {
            if (i_c == 0 || i_c == i_r)
                row[i_c] = 1;
            else
            {
                int prev1 = triangle[i_r - 1][i_c - 1];
                int prev2 = triangle[i_r - 1][i_c];
                if (prev1 == -1 || prev2 == -1 || prev1 + prev2 > 1000000)
                {
                    row[i_c] = -1;
                    count++;
                }
                else
                {
                    row[i_c] = prev1 + prev2;
                }
            }
        }
    }

    std::cout << count;
}
