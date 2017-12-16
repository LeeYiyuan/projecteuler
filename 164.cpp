/*
    For each length, we consider the possible last two digits. For each possible
    last two digits, we consider what the previous two digits, i.e. 3rd and 2nd
    last digits are, allowing us to set up a recurrce relation for the cases
    from the previous length, thereby transforming the problem into a dynamic
    programming problem.
*/

#include <iostream>
#include <vector>

int main()
{
    int n = 20;
    std::vector<unsigned long long> counts(100), _counts(100);
    
    for (int i = 0; i < 100; i++)
        counts[i] = i >= 10 && ((i % 10) + (i / 10) <= 9);

    for (int i = 0; i < n - 2; i++)
    {
        for (int j = 0; j < 100; j++)
            for (int k = 0; k + (j % 10) + (j / 10) <= 9; k++)
                _counts[j] += counts[(k * 10) + (j / 10)];

        counts = std::move(_counts);
        _counts = std::vector<unsigned long long>(100);
    }

    unsigned long long count = 0;
    for (unsigned long long const &c : counts)
        count += c;

    std::cout << count;    
}