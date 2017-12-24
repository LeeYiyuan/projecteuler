/*
    For each possible inner square width, we enumerate the possible outline
    widths and count how many tiles are used and then increment the counter
    for that number of tiles by one.

    Afterwards we count how many number of tiles has counter between 1 and 10,
    inclusive on both ends.
*/

#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>

int main()
{
    int n = 1000000;
    std::vector<int> counts(n + 1, 0);

    for (uint64_t a = 1; 4 * a + 4 <= n; a++)
        for (uint64_t b = a + 2; b * b - a * a <= n; b += 2)
            counts[b * b - a * a]++;

    int total = 0;
    for (int count : counts)
        if (count >= 1 && count <= 10)
            total++;
    
    std::cout << total;
}