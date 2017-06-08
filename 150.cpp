/*
    For each row, we look for the minimum triangle sums whose base lie on that
    row. For each row, this is done by adding diagonals to the right one at a
    time, and for each diagonal added, we remove antidiagonals from the left one
    at a time and collect the sum that is minimal across the entire process.
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

int main()
{
    std::vector<int> s;
    unsigned long long t = 0;
    for (int k = 1; k <= 500500; k++)
    {
        t = (615949 * t + 797807) % (1 << 20);
        s.emplace_back(t - (1 << 19));
    }

    std::vector<std::vector<int>> triangle;
    int i = 0;
    for (int r = 0; r < 1000; r++)
    {
        triangle.emplace_back(r + 1);
        for (int c = 0; c <= r; c++)
            triangle.back()[c] = s[i++];
    }

    int sum_min = INT_MAX;
    std::vector<int> subtracts(triangle.size(), 0);
    std::vector<int> sums(triangle.size(), 0);
    for (int r = 0; r < triangle.size(); r++)
    {
        std::vector<int> _sums(triangle[r].size(), 0);
        int s = 0;
        for (int c = 0; c < triangle[r].size(); c++)
        {
            subtracts[c] += triangle[r][c];
            s += triangle[r][c];
            if (c > 0)
                _sums[c] += sums[c - 1];
            _sums[c] += s;
        }
        sums = _sums;
        for (int s : sums)
        {
            for (int &sub : subtracts)
            {
                sum_min = std::min(sum_min, s);
                s -= sub;
            }
        }
    }

    std::cout << sum_min;
}
