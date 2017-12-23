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

    Since A is the sequence of iterated function values of some function that 
    maps the finite set {0, 1}^{4n + 4} to itself, A must eventually become
    periodic.

    By considering:

        1) the number of m that are in U(2, 2n + 1) up before A_m starts turns
           periodic,
        2) the value of m for which A_m starts to turn periodic,
        3) the number of elements in U(2, 2n + 1) in each period, and
        4) the length of each cycle

    we can calculate U(2, 2n + 1)_k for large values of k rather efficiently
    due to the aforementioned periodicity.

    We use uint64 to encode each A_m. Note that this is possible for each of
    n = 2, ..., 10 because the maximum dimension of the codomain of A is
    at most 4 * 10 + 4 = 44 which can fit entirely into a uint64. Using bit
    operators allow us to calculate A_{m + 1} given A_m rather efficiently.
    
    The tortise and hare algorithm is used to compute details of the cycles.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdint>

// Naive and inefficient method to generate the initial A_m.
void generate_A(int n, int m, uint64_t &A, uint64_t &k)
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
        A |= uint64_t(1) << (m - index);

    k = indices.size();
}

bool move_next(int n, int m, uint64_t &A)
{
    bool result = (m != 8 * (n + 1)) & (((A >> (2 - 1)) & 1) ^ ((A >> (4 * (n + 1) - 1)) & 1));
    A <<= 1;
    A |= result;
    return result;
}

int main()
{   
    uint64_t total = 0;
    for (uint64_t n = 2; n <= 10; n++)
    { 
        uint64_t mA = 4 * (n + 1);
        uint64_t A;  
        uint64_t kA;
        generate_A(n, mA, A, kA);

        uint64_t mB = mA, B = A, kB = kA;

        do
        {
            mA++;
            if (move_next(n, mA, A)) kA++;
            mB++;
            if (move_next(n, mB, B)) kB++;
            mB++;
            if (move_next(n, mB, B)) kB++;
        } while (A != B);

        // Note that the cycle may not and need not necessarily be fundamental.
        uint64_t cycle_length = mB - mA;
        uint64_t count_per_cycle = kB - kA;
        uint64_t number_of_cycles = (100000000000 - kB) / count_per_cycle;

        mB += number_of_cycles * cycle_length;
        kB += number_of_cycles * count_per_cycle;

        while (kB < 100000000000)
        {
            mB++;
            if (move_next(n, mB, B)) kB++;
        }

        total += mB;
    }
    std::cout << total;
}