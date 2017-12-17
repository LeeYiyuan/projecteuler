/*
    Consider a triangle ABC and a point D. One can observe that if D lies inside
    ABC, then

        area(ABC) = area(ABD) + area(ACD) + area(BCD)

    If on the other hand, D lies outside ABC, then

        area(ABC) < area(ABD) + area(ACD) + area(BCD)

    which forms the basis of our search filter.

    To find the area of triangle ABC given points ABC, we can use Heron's
    formula on sides AB, BC, AC. In order to reduce rounding error, we use a
    modified version that only does the square root at the end.
*/

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstdint>
#include "io_util.h"
#include "string_util.h"

typedef std::pair<int, int> point_type;

uint64_t get_distance2(point_type const &A, point_type const &B)
{
    return (A.first - B.first) * (A.first - B.first) + (A.second - B.second) * (A.second - B.second);
}

double get_area(point_type const &A, point_type const &B, point_type const &C)
{
    uint64_t la2 = get_distance2(A, B);
    uint64_t lb2 = get_distance2(A, C);
    uint64_t lc2 = get_distance2(B, C);
    return std::sqrt(4 * la2 * lb2 - (la2 + lb2 - lc2) * (la2 + lb2 - lc2)) / 4;
}

bool is_in_triangle(point_type const &A, point_type const &B, point_type const &C, point_type const &P)
{
    double total_area = get_area(A, B, P) + get_area(A, C, P) + get_area(B, C, P);
    double triangle_area = get_area(A, B, C);
    return total_area == triangle_area;
}

int main()
{
    int count = 0;
    std::string triangles_string = util::read_file("102_triangles.txt");
    for (std::string &triangle_row_string : util::split(triangles_string, '\n'))
    {
        std::vector<std::string> coord_strings = util::split(triangle_row_string, ',');
        point_type A(std::stoi(coord_strings[0]), std::stoi(coord_strings[1]));
        point_type B(std::stoi(coord_strings[2]), std::stoi(coord_strings[3]));
        point_type C(std::stoi(coord_strings[4]), std::stoi(coord_strings[5]));
        if (is_in_triangle(A, B, C, point_type(0, 0)))
            count++;
    }
    std::cout << count;
}
