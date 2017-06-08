/*
    Let p(n, k) be the number of ways to partition n into parts that are at most
    k. Additionally, each part must be an element of C = {1, 2, 5, 10, 20, 50,
    100, 200}.

    Each partition must have a maximum value. This maximum value must be an
    element of C (because all parts are in C). We count each possible case to
    get:

        p(n, k) = \sum_{c in C | c <= min(n, k)} p(n - c, c)

    with p(0, k) = 1 for any k.

    We need p(200, 200).
*/

#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> C = { 1, 2, 5, 10, 20, 50, 100, 200 };

int partitions(int n, int k)
{
    if (n == 0)
        return 1;
    int sum = 0;
    for (int i = 0; i < C.size() and C[i] <= std::min(n, k); i++)
        sum += partitions(n - C[i], C[i]);
    return sum;
}

int main()
{
    std::cout << partitions(200, 200);
}
