/*
    A pretty straightforward and naive solution that calculates intersection
    using vectors and matrices, and doing the necessary checks.

    The solution is simplified to use as little fractions as possible. Only 
    after an intersection is computed is a fraction (in its lowest form) return
    as a 4-tuple of numerators and denominators stored for duplicate checking. 
    
    Note that the fraction is in its lowest term so we can use the 4-tuple
    directly as a key in std::set, since all we're checking for is duplicates.
*/

#include <iostream>
#include <vector>
#include <set>

int sign(int x) { return (x > 0) - (x < 0); }
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

bool get_intersection(int x1, int y1, int x2, int y2, int x1_, int y1_, int x2_, int y2_, std::vector<int> &result)
{
    int a = x2 - x1;
    int b = x1_ - x2_;
    int c = y2 - y1;
    int d = y1_ - y2_;
    int e = x1_ - x1;
    int f = y1_ - y1;

    int det = a * d - b * c;

    if (det == 0) return false;

    int g = det * x1 + (d * e - b * f) * (x2 - x1);
    int h = det * y1 + (d * e - b * f) * (y2 - y1);

    if (sign(g - x1 * det) * sign(g - x2 * det) > 0) return false;
    if (sign(h - y1 * det) * sign(h - y2 * det) > 0) return false;
    if (sign(g - x1_ * det) * sign(g - x2_ * det) > 0) return false;
    if (sign(h - y1_ * det) * sign(h - y2_ * det) > 0) return false;
    if (g == x1 * det && h == y1 * det) return false;
    if (g == x2 * det && h == y2 * det) return false;
    if (g == x1_ * det && h == y1_ * det) return false;
    if (g == x2_ * det && h == y2_ * det) return false;

    int zg = gcd(g, det);
    int zh = gcd(h, det);

    result[0] = g / zg;
    result[1] = det / zg;
    result[2] = h / zh;
    result[3] = det / zh;
    
    return true;
}

int main()
{
    std::vector<int> numbers(5000 * 4);
    std::set<std::vector<int>> intersections;

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
            std::vector<int> intersection(4);
            if (get_intersection(numbers[i * 4], numbers[i * 4 + 1], numbers[i * 4 + 2], numbers[i * 4 + 3], numbers[j * 4], numbers[j * 4 + 1], numbers[j * 4 + 2], numbers[j * 4 + 3], intersection))
                intersections.emplace(intersection);
        }
    }

    std::cout << intersections.size() << std::endl;
}