/*
    Similar to #135.
*/

#include <iostream>
#include <unordered_map>

int main()
{
    int n_max = 50000000;
    std::unordered_map<int, int> solution_counts;
    for (int y = 0; y < n_max; y++)
    {
        int x = y * 5 / 4 + 1;
        int n = y * (4 * x - 5 * y);
        while (n < n_max && x < 2 * y)
        {
            solution_counts[n]++;
            x++;
            n += 4 * y; // Because 4(x + 1)y - 5y^2 = (4xy - 5y^2) + 4y
        }
    }

    int count = 0;
    for (auto &pair : solution_counts)
        if (pair.second == 1)
            count++;

    std::cout << count;
}
