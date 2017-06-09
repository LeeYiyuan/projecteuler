/*
    For n, consider factors d >= 2. Then mdrs(n) = \max(drs(d) + mdrs(n / d)).
    Additionally, we only need to consider up to d <= \sqrt{n} because for d >
    \sqrt{n}, we can swap d with the other factor d' < \sqrt{n}, and (d', d)
    would have already been considered before.

    We use dynamic programming with seed value mdrs(1) = 1 to generate a n ->
    mdrs(n) table.
*/

#include <iostream>
#include <vector>
#include <algorithm>

int drs(int n)
{
    int result = n;
    while (result >= 10)
    {
        int _result = 0;
        while (result > 0)
        {
            _result += result % 10;
            result /= 10;
        }
        result = _result;
    }
    return result;
}

int main()
{
    int limit = 1000000;
    std::vector<int> mdrs_table(limit, 0);
    mdrs_table[0] = 0;
    mdrs_table[1] = 1;

    int sum = 0;
    for (int n = 2; n < limit; n++)
    {
        mdrs_table[n] = drs(n);
        for (int d = 2; d * d <= n; d++)
            if (n % d == 0)
                mdrs_table[n] = std::max(mdrs_table[n], drs(d) + mdrs_table[n / d]);
        sum += mdrs_table[n];
    }

    std::cout << sum;
}
