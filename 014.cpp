#include <iostream>
#include <cstdint>

uint64_tcollatz(uint64_tn)
{
    return n % 2 == 0 ? n / 2 : 3 * n + 1;
}

int main()
{
    int longest_starting_number;
    int longest_chain_length = -1;

    for (int i = 0; i < 1000000; i++)
    {
        uint64_tj = i;
        int length = 1;
        while (j > 1)
        {
            j = collatz(j);
            length++;
        }
        if (length > longest_chain_length)
        {
            longest_starting_number = i;
            longest_chain_length = length;
        }
    }

    std::cout << longest_starting_number;
}
