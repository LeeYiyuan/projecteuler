/*
    Naive solution.
*/

#include <vector>
#include <unordered_set>
#include <iostream>

int main()
{
    std::vector<int> factorials = {
        1,
        1,
        2 * 1,
        3 * 2 * 1,
        4 * 3 * 2 * 1,
        5 * 4 * 3 * 2 * 1,
        6 * 5 * 4 * 3 * 2 * 1,
        7 * 6 * 5 * 4 * 3 * 2 * 1,
        8 * 7 * 6 * 5 * 4 * 3 * 2 * 1,
        9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1
    };

    int count = 0;
    for (int n = 1; n < 1000000; n++)
    {
        int _n = n;
        std::unordered_set<int> sequence;
        while (sequence.find(_n) == sequence.end())
        {
            sequence.emplace(_n);
            int next = 0;
            while (_n > 0)
            {
                next += factorials[_n % 10];
                _n /= 10;
            }
            _n = next;
        }
        if (sequence.size() == 60)
            count++;
    }

    std::cout << count;
}
