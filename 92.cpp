/*
Separate the starting numbers into two groups: The first are the starting numbers
that eventually arrive at 1; And the second, those that eventually arrive at 89.

We also make the following observation: For some starting number n, every starting
number that is an element of the chain of n is also in the same group as n. With
this we can cache some results and avoid some computations.
*/

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>

bool check(std::unordered_map<int, bool> &cache, int n)
{
    std::vector<int> affected_starting_numbers;
    while (cache.find(n) == cache.end())
    {
        affected_starting_numbers.emplace_back(n);
        int _n = n;
        n = 0;
        while (_n > 0)
        {
            n += (_n % 10) * (_n % 10);
            _n /= 10;
        }
    }
    for (int &affected_starting_number : affected_starting_numbers)
        cache[affected_starting_number] = cache[n];
    return cache[n];
}

int main()
{
    std::unordered_map<int, bool> cache = {
        { 1, false },
        { 89, true }
    };
    int count = 0;
    for (int n = 1; n < 10000000; n++)
        count += check(cache, n);

    std::cout << count;
}
