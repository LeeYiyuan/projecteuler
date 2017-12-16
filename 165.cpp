/*
    A pretty straightforward and naive solution that calculates intersection
    using vectors and matrices, and doing the necessary checks.
*/

#include <iostream>
#include <vector>
#include <gmpxx.h>
#include <set>

bool get_intersection(int x1, int y1, int x2, int y2, int x1_, int y1_, int x2_, int y2_, mpq_class &result_x, mpq_class &result_y)
{
    int a = x2 - x1;
    int b = x1_ - x2_;
    int c = y2 - y1;
    int d = y1_ - y2_;
    int e = x1_ - x1;
    int f = y1_ - y1;

    int det = a * d - b * c;

    if (det == 0) return false;

    mpq_class x(det * x1 + (d * e - b * f) * (x2 - x1), det); x.canonicalize();
    mpq_class y(det * y1 + (d * e - b * f) * (y2 - y1), det); y.canonicalize();
    
    if (sgn(x - x1) * sgn(x - x2) > 0) return false;
    if (sgn(y - y1) * sgn(y - y2) > 0) return false;
    if (sgn(x - x1_) * sgn(x - x2_) > 0) return false;
    if (sgn(y - y1_) * sgn(y - y2_) > 0) return false;
    if (x == x1 && y == y1) return false;
    if (x == x2 && y == y2) return false;
    if (x == x1_ && y == y1_) return false;
    if (x == x2_ && y == y2_) return false;

    result_x = x;
    result_y = y;

    return true;
}

int main()
{
    std::vector<int> numbers(5000 * 4);
    std::set<std::vector<mpq_class>> intersections;

    unsigned long long s = 290797;
    for (int i = 0; i < numbers.size(); i++)
    {
        s = (s * s) % 50515093;
        numbers[i] = s % 500;
    }

    for (int i = 0; i < numbers.size() / 4; i++)
    {
        for (int j = i + 1; j < numbers.size() / 4; j++)
        {
            mpq_class x, y;
            if (get_intersection(numbers[i * 4], numbers[i * 4 + 1], numbers[i * 4 + 2], numbers[i * 4 + 3], numbers[j * 4], numbers[j * 4 + 1], numbers[j * 4 + 2], numbers[j * 4 + 3], x, y))
                intersections.emplace(std::vector<mpq_class>{x, y});
        }
    }

    std::cout << intersections.size() << std::endl;
}