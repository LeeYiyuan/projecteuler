/*
    Let the initial cuboid have dimensions l x w x d. At each step, we consider
    the top view of the cuboid.

    The cuboids required to cover the top of the cuboid is exactly the area of
    cuboid from the top view. The cuboids required to cover the side of the
    cuboid (with respect to the top view) is exactly those that cover the
    perimeter of the current cuboid area.

    In particular, for layer i = 0, 1, ..., let a_i be the area of the cuboid
    from the top view, and let p_i be the number of cuboids required to cover
    the perimeter of a_i. Then,

        a_0 = l * w
        p_i = 2 * (l + w) + 4 * i
        a_i = a_{i - 1} + p_{i - 1}

    Let c_i be the total number of cuboids required to cover the current figure
    at layer i = 0, 1, .... Then c_i is just

        c_i = 2 * a_i + d * p_i

    With this we can get a generator for the number of cuboids needed for each
    layer given the original cuboid (l, w, d). We shall name this set of numbers
    layerCounts(l, w, d).

    Next, we guess an upper bound n_max = 20000 for the required layer count n
    such that C(n) = 1000.. For each (l, w, d), we take all n in layerCounts(l,
    w, d) that are at most n_max and add it to the respective counter for n.

    After everything, we look for the least n whose counter is equal to 1000.

    In case you are wondering how I guessed n_max: I actually had a function
    that determines, for a given n, the value of C(n). However it is inefficient
    to calculate C(n) for successive values of n, because cuboids are considered
    repeatedly.

    As such, I plugged in different values of n and found that at C(n) exceeds
    1000 at around n = 20000. I then modified the script in such a way that
    C(1), C(2), ..., C(n_max = 20000) can be calculated in such a way where
    cuboids are not reconsidered again.
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>
#include <algorithm>

std::vector<int> get_layer_counts(int l, int w, int d, int n_max)
{
    std::vector<int> layer_counts;

    int area = l * w;
    int step = 0;
    int perimeter = 2 * (l + w) + 4 * step;
    int layer_count = 2 * area + d * perimeter;

    while (layer_count <= n_max)
    {
        layer_counts.emplace_back(layer_count);
        area += perimeter;
        step++;
        perimeter = 2 * (l + w) + 4 * step;
        layer_count = 2 * area + d * perimeter;
    }

    return layer_counts;
}

int get_minimum_cuboid_count(int l, int w, int d)
{
    return 2 * l * w + d * 2 + (l + w);
}

int main()
{
    std::unordered_map<int, int> counter;
    int n_max = 20000;
    int l = 1;
    while (get_minimum_cuboid_count(l, 1, 1) <= n_max)
    {
        int w = 1;
        while (w <= l && get_minimum_cuboid_count(l, w, 1) <= n_max)
        {
            int d = 1;
            while (d <= w && get_minimum_cuboid_count(l, w, d) <= n_max)
            {
                for (int &layer_count : get_layer_counts(l, w, d, n_max))
                    counter[layer_count]++;
                d++;
            }
            w++;
        }
        l++;
    }

    int n_min = INT_MAX;
    for (auto &pair : counter)
        if (pair.second == 1000)
            n_min = std::min(n_min, pair.first);

    std::cout << n_min;
}
