/*
    We start with a (r - 1) x c grid. We consider the additional number of
    rectangles that can be formed by extending the grid by either one row or one
    column.

    Suppose we extend by one row to get a r) x c grid. The additional rectangles
    that can be formed are those that overlaps with the r th row. There are

        (r)(c + (c - 1) + ... + 1) = (r)(c)(c + 1) / 2

    such cases.

    Now comes the tedious part: Diagonal rectangles. Each diagonal rectangle
    must end at the bottom most squares (the ones touching the bottom most edge
    of the grid), or at the horizontal array of squares above this.

    For each bottom, we loop through the possible left, right and top
    coordinates of every possible diagonal rectangle and count how many there
    are. The loop can be done by sliding.

    First we fix the bottom position. Then, we slide out towards the top left
    one square at a time until the left most square exceeds the left border of
    the grid. For each bottom and left position, we slide out towards the top
    right until either the top most square exceeds the top border of the grid,
    or until the right most square exceeded the right border of the grid.

    It will be very helpful indeed to draw out a sufficiently large grid, say 6
    x 10, to visualize what happens if you extend the rows. You can cover up the
    unnecessary parts with pieces of paper if you only want to see what happens
    when you extend a grid to dimensions r x c with r <= 6, c <= 10.

    The number of cases from sliding is summed up to give the number of new
    diagonal rectangles that overlaps with the new row.

    Extending a r x (c - 1) grid by one column is equivalent to extending a (c -
    1) x r grid by one row, so we can use the same procedure for extending along
    the other perpendicular direction by transposing the dimensions.
*/

#include <iostream>
#include <vector>

int count_straight_rectangles(int r, int c)
{
    return r * c * (c + 1) / 2;
}

int count_diagonal_rectangles(int r, int c)
{
    std::vector<std::pair<int, int>> bottoms;
    std::pair<int, int> bottom = { 0, 1 };
    while (bottom.second < 2 * c - 1)
    {
        bottoms.emplace_back(bottom);
        bottom.second += 2;
    }
    bottom = { 1, 0 };
    while (bottom.second < 2 * c - 1)
    {
        bottoms.emplace_back(bottom);
        bottom.second += 2;
    }

    int count = 0;
    for(std::pair<int, int> &bottom : bottoms)
    {
        std::pair<int, int> left(bottom);
        while (left.second >= 0 && left.first < 2 * r - 1)
        {
            std::pair<int, int> right(bottom);
            std::pair<int, int> top(left);
            while (right.second < 2 * c - 1 && top.first < 2 * r - 1)
            {
                count++;
                right.second++;
                right.first++;
                top.second++;
                top.first++;
            }
            left.second--;
            left.first++;
        }
    }

    return count;
}

void extend(int &r, int &c, int &count)
{
    r++;
    count += count_straight_rectangles(r, c) + count_diagonal_rectangles(r, c);
}

int main()
{
    int count_total = 0;

    int r = 1;
    int c = 1;
    int count = 1;
    for (int row = 1; row <= 43; row++)
    {
        int _r = c;
        int _c = r;
        int _count = count;
        for (int column = 1; column <= 47; column++)
        {
            count_total += _count;
            extend(_r, _c, _count);
        }
        extend(r, c, count);
    }

    std::cout << count_total;
}
