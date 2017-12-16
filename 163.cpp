/*
    The overall strategy is to consider all possible vertices of triangles,
    and to search through a relevant adjacency list how many triangles there
    are.

    First, we split the lines into three grids, and then color these grids:

    Blue:   Lines parallel or perpendicular to the line joining the center of
            the triangle to the top vertex.
    Red:    Lines parallel or perpendicular to the line joining the center of 
            the triangle to the bottom left vertex.
    Green:  Lines parallel or perpendicular to the line joining the center of 
            the triangle to the bottom right vertex.
    
    Notice that for every possible point that can become the vertex of some 
    triangle, the adjacent points can be partitioned into adjacent points in
    each of the three grids. Hence we can consider the three grids separately
    when generating the adjaceny list for possible vertices of triangles.

    Note that we can form an orthogonal basis using each of this grid. For each
    grid, we set the center of the triangle as the origin. For each color, we 
    have as basis:

    Blue:   (0, 1) is the height of one size 1 triangle along the direction of
            the top of the triangle from the origin.
            (1, 0) is the same distance to the right of the origin.
    Green:  (0, 1) is the height of one size 1 triangle along the direction of
            the bottom left vertex of the triangle from the origin.
            (1, 0) is the same distance in the perpendicular direction towards
            the left edge of the triangle.
    Red:    (0, 1) is the height of one size 1 triangle along the direction of
            the bottom right vertex of the triangle from the origin.
            (1, 0) is the same distance in the perpendicular direction towards
            the right edge of the triangle.

    Denote B, R, G as the bases for the blue, red, and green grids respectively.
    Let a point P = X^Y denote having coordinates X in basis Y. 
    
    Let T_{RB} be the transition matrix from B to R. Note that

        [2; 0]^B = [-1; -1]^R
        [0; 2/3]^B = [1; -1/3]^R
    
    where we exploit the fact that the inradius of an equilateral triangle is
    1/3 that of its altitude. This gives us

        T_{RB} = [-1 1;-1 -1/3] * [1/2 0;0 1/c]
               = [-1 3;-1 -1] / 2
    
    Note also that T_{RB} = T_{GR} = T_{BG}. This gives us a very clean way
    to transform coordinates between the different bases.

    The generation of the adjacency list is relatively trivial afterwards. I
    used the first method I could think of. You only need to consider one of the 
    three grids, because if M^Y and N^Y are adjacent, then so is M^Z and N^Z for 
    the other Z's. You can use T_{RB} to find (M^Z)_Y, (N^Z)_Y.
    
    For the search, I went through each point A, and for each point A, I went 
    through distinct pairs of adjacent points (B, C) such that A, B, C are
    not collinear. This is to exclude straight lines. If B and C are adjacent, 
    then we have a hit.

    As an optimization, note that all coordinates have denominator dividing
    6, so we can scale everything by 6 and use integers instead of having to
    deal with fractions.
*/

#include <iostream>
#include <unordered_set>
#include <unordered_map>

int make_point(int x, int y) { return (x << 16) | (y & 0xFFFF); }
int get_x(int point) { return ((point >> 31) & 1) ? (0xFFFF0000 | (point >> 16)) : (point >> 16); }
int get_y(int point) { return ((point >> 15) & 1) ? (0xFFFF0000 | (point & 0xFFFF)) : (point & 0xFFFF); }

int transform(int point, int basis_changes)
{
    for (int i = 0; i < basis_changes; i++)
        point = make_point((-get_x(point) + 3 * get_y(point)) / 2, (-get_x(point) - get_y(point)) / 2);
    return point;
}

int main()
{
    int n = 36;

    std::unordered_map<int, std::unordered_set<int>> adjacency;
    for (int c = 0; c < n; c++)
    {
        for (int r1 = 2 * c; r1 < 2 * n; r1++)
        {
            for (int r2 = r1 + 1; r2 < 2 * n + 1; r2++)
            {
                int offset1 = make_point(6 * c, r1 % 2 == 0 ? 3 * r1 : r1 % 4 == (c % 2 == 0 ? 1 : 3) ? 3 * (r1 - 1) + 4 : 3 * (r1 - 1) + 2);
                int offset2 = make_point(6 * c, r2 % 2 == 0 ? 3 * r2 : r2 % 4 == (c % 2 == 0 ? 1 : 3) ? 3 * (r2 - 1) + 4 : 3 * (r2 - 1) + 2);
                int endpoint1 = make_point(get_x(offset1), 4 * n - get_y(offset1));
                int endpoint2 = make_point(get_x(offset2), 4 * n - get_y(offset2));

                for (int basis = 0; basis < 3; basis++)
                {
                    adjacency[transform(endpoint1, basis)].emplace(transform(endpoint2, basis));
                    adjacency[transform(endpoint2, basis)].emplace(transform(endpoint1, basis));
                    if (c > 0)
                    {
                        adjacency[transform(make_point(-get_x(endpoint1), get_y(endpoint1)), basis)].emplace(transform(make_point(-get_x(endpoint2), get_y(endpoint2)), basis));
                        adjacency[transform(make_point(-get_x(endpoint2), get_y(endpoint2)), basis)].emplace(transform(make_point(-get_x(endpoint1), get_y(endpoint1)), basis));
                    }
                }
            }
        }
    }
    for (int i = 1; i < n + 1; i++)
    {    
        for (int c1 = -i; c1 < i; c1++)
        {    
            for (int c2 = c1 + 1; c2 < i + 1; c2++)
            {
                int offset1 = make_point(6 * c1, 6 * i), offset2 = make_point(6 * c2, 6 * i);
                int endpoint1 = make_point(get_x(offset1), 4 * n - get_y(offset1));
                int endpoint2 = make_point(get_x(offset2), 4 * n - get_y(offset2));

                for (int basis = 0; basis < 3; basis++)
                {
                    adjacency[transform(endpoint1, basis)].emplace(transform(endpoint2, basis));
                    adjacency[transform(endpoint2, basis)].emplace(transform(endpoint1, basis));
                }
            }
        }
    }
    
    int count = 0;
    for (auto const &pair : adjacency)
    {
        int point = pair.first;
        std::unordered_set<int> const &adjacent_points = pair.second;

        for (auto it1 = adjacent_points.begin(); it1 != adjacent_points.end(); ++it1)
        {
            auto it2 = it1;
            ++it2;
            for (; it2 != adjacent_points.end(); adjacency[*(it2++)].erase(point))
                if ((get_y(point) - get_y(*it1)) * (get_x(point) - get_x(*it2)) != (get_y(point) - get_y(*it2)) * (get_x(point) - get_x(*it1)))
                    if (adjacency[*it1].find(*it2) != adjacency[*it1].end() && adjacency[*it2].find(*it1) != adjacency[*it2].end())
                        count++;
            adjacency[*it1].erase(point);
        }
    }

    std::cout << count;
}