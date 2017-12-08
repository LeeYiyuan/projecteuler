/*
    We use dynamic programming across the number of columns. 
    
    At each step, we consider the configurations that lead to at least one block
    in the last column, and compute a recurrence back to the cases from the
    previous step, where the blocks end at the previous column.

    The DFS involved is such that repeated cases are not considered. This is 
    done by noticing that we can set up some sort of partial order on the set of
    (T, L) where T is a tile and L is a location.
*/

#include <iostream>
#include <vector>

typedef unsigned long long ull;

// Generates counts via brute force, used only for base case.
void generate(int rows, int columns, ull map, std::vector<ull> const& blocks, int block_index, std::vector<ull> &counts)
{
    counts[map]++; // Assume there is one way to arrange nothing.
    for (int i = block_index; i < blocks.size(); i++)
    {
        ull block = blocks[i];
        if ((map & block) == 0)
        {
            generate(rows, columns, map | block, blocks, i + 1, counts);
        }
    }
}

// Linear transformation underlying the dynamic programming part.
ull transform(int rows, int columns, ull map, std::vector<ull> const& blocks, int block_index, std::vector<ull> const &counts)
{
    if ((map & ((ull(1) << rows) - 1)) == 0)
        return counts[map >> rows];

    ull result = 0;
    for (int i = block_index; i < blocks.size(); i++)
        if ((map & blocks[i]) == blocks[i])
            result += transform(rows, columns, map ^ blocks[i], blocks, i + 1, counts);

    return result;
}

int main()
{
    int rows = 9, columns = 12;
    std::vector<ull> initial_blocks, blocks;
    
    // Generates blocks required for base case and dynamic programming.
    for (int c = 0; c < 2; c++)
    {
        for (int r = 0; r < rows - 2; r++)
        {
            initial_blocks.emplace_back(0b111 << (c * rows + r));
            if (c == 0) blocks.emplace_back(initial_blocks.back());
        }
    }
    for (int r = 0; r < rows - 1; r++)
    {
        initial_blocks.emplace_back(((0b01 << rows) | 0b11) << r);
        blocks.emplace_back(initial_blocks.back());
        initial_blocks.emplace_back(((0b11 << rows) | 0b01) << r);
        blocks.emplace_back(initial_blocks.back());
        initial_blocks.emplace_back(((0b11 << rows) | 0b10) << r);
        blocks.emplace_back(initial_blocks.back());
        initial_blocks.emplace_back(((0b10 << rows) | 0b11) << r);
        blocks.emplace_back(initial_blocks.back());
    }
    for (int r = 0; r < 9; r++)
        blocks.emplace_back(((0b1 << (2 * rows)) | (0b1 << rows) | 1) << r);
    
    // Computes count for base case.
    std::vector<ull> counts(1 << (2 * rows)), _counts(1 << (2 * rows));
    generate(rows, columns, 0, initial_blocks, 0, counts);

    // Computes count for number of columns = 3, 4, ..., 11 using dynamic programming.
    for (int i = 2; i < 11; i++)
    {
        std::vector<ull> _counts(1 << (2 * rows));
        for (ull j = 0; j < (1 << 2 * rows); j++)
            _counts[j] = transform(rows, columns, j | (((1 << rows) - 1) << (2 * rows)), blocks, 0, counts);
        
        std::swap(counts, _counts);
    }

    // Computes count for filled case for number of columns = 12.
    std::cout << transform(rows, columns, (1 << (3 * rows)) - 1, blocks, 0, counts);
}