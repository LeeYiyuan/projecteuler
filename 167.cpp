/*
    For n = 2, ..., 10, it turns out that the only even values in U(2, 2n + 1)
    are 2 and 4n + 4, and all other values in the sequence must be odd. Hence,
    to check if m is in U(2, 2n + 1), we only need to check if exactly one of
    m - 2 and m - (4n - 4) is in U(2, 2n + 1).

    For each m = 2n + 2, ..., denote A_m to be the (4n + 4)-tuple such that

        (A_m)_i = 1     if  m - i \in U(2, 2n + 1),
                  0     otherwise
    
    for i = 0, ..., 4n + 3. As discussed earlier, we have the following
    recurrence relation on A:

        (A_{m + 1})_i = (A_m)_1 ^ (A_m)_{4n + 3}    if i = 0,
                        (A_m)_{i - 1}               otherwise
    
    Note that an exception has to be made for the case where m = 2 * (4n + 4),
    in which case m is written as the sum of two non-distinct integers.

    Since A is a sequence in the finite set {0, 1}^{4n + 4} and it can be 
    described using a first order homogeneous linear recurrence relation, then
    by the Pigeonhole Principle, the sequence must be periodic eventually.

    By considering:

        1) the number of m that are in U(2, 2n + 1) up before A_m starts cycling,
        2) the value of m for which A_m starts to cycle,
        3) the number of elements in U(2, 2n + 1) in each cycle, and
        4) the period of each cycle,

    we can calculate U(2, 2n + 1)_k for large values of k rather efficiently
    due to the aforementioned periodicity.

    We use uint64 to encode each A_m. Note that this is possible for each of
    n = 2, ..., 10 because the maximum dimension of the codomain of A is
    at most 4 * 10 + 4 = 44 which can fit entirely into a uint64. Using bit
    operators allow us to calculate A_{m + 1} given A_m rather efficiently.
    Also, uint64's are easy to put in a hashmap to allow for O(1) lookup when
    checking for a cycle.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>

typedef unsigned long long ull;

// Naive and inefficient method to generate the initial A_m.
void generate_A(int n, int m, ull &A, ull &k)
{
    std::vector<int> indices = { 2, 2 * n + 1 };
    for (int i = 2 * n + 2; i <= m; i++)
    {
        int count = 0;
        for (int j = 0; i - indices[j] > indices[j] && (count += std::binary_search(indices.begin(), indices.end(), i - indices[j])) <= 1; j++);
        if (count == 1) indices.emplace_back(i);
    }

    A = 0;
    for (int index : indices)
        A |= ull(1) << (m - index);

    k = indices.size();
}

bool move_next(int n, int m, ull &A)
{
    bool result = (m != 8 * (n + 1)) & (((A >> (2 - 1)) & 1) ^ ((A >> (4 * (n + 1) - 1)) & 1));
    A <<= 1;
    A |= result;
    return result;
}

int main()
{   
    ull total = 0;
    for (ull n = 2; n <= 10; n++)
    { 
        ull m = 4 * (n + 1);
        ull A;  
        ull k;
        generate_A(n, m, A, k);

        std::unordered_map<ull, std::pair<ull, ull>> history;

        do
        {
            history[A] = { m, k };
            m++;
            if (move_next(n, m, A)) k++;
        } while (history.find(A) == history.end());

        ull wavelength = m - history[A].first;
        ull count_per_period = k - history[A].second;
        ull number_of_periods = (100000000000 - k) / count_per_period;

        m += number_of_periods * wavelength;
        k += number_of_periods * count_per_period;

        while (k < 100000000000)
        {
            m++;
            if (move_next(n, m, A)) k++;
        }

        total += m;
    }
    std::cout << total;
}
