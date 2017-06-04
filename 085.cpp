#include <utility>
#include <iostream>

std::pair<int, int> get_best_number_of_rows(int total, int C)
{
    int t = 0;
    int y = 1;
    while (true)
    {
        int row_sum = 0;
        for (int x = 1; x <= C; x++)
            row_sum += x * y;
        if (t + row_sum > total)
            return std::pair<int, int>(y - 1, t);
        t += row_sum;
        y++;
    }
}

int main()
{
    int best_count = -1;
    int best_columns;
    int best_rows;

    int columns = 0;
    int rows = 1;
    while (rows > 0)
    {
        columns++;

        std::pair<int, int> p = get_best_number_of_rows(2000000, columns);
        rows = p.first;
        int count = p.second;

        if (count > best_count)
        {
            best_count = count;
            best_columns = columns;
            best_rows = rows;
        }
    }

    std::cout << best_rows * best_columns;
}
