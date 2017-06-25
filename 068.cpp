/*
    We take 5-combinations of the 10 digits for the outer ring. For each outer
    ring combination, we have a corresponding inner ring combination.

    We permutate the largest 4 elements of the outer ring to get outer ring
    permutations that do not repeat cyclically.

    Then, for each outer ring permutation, we permutate the inner rings. Here,
    we allow inner permutations that repeat cyclically. This is because for
    every class of cyclically equivalent inner ring permutations, we can rotate
    some corresponding characterizing inner ring permutation around and each
    will combine differently with the outer ring.

    For each outer ring and inner ring permutation pair that is magic, we take
    the required string. We find the largest 16-digit string across all (outer
    ring, inner ring) pairs.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

bool is_magic(std::vector<int> const &outer, std::vector<int> const &inner)
{
    int total = outer[0] + inner[0] + inner[1];
    for (int i = 1; i < 5; i++)
        if (total != outer[i] + inner[i] + inner[(i + 1) % 5]) return false;
    return true;
}

std::string get_string(std::vector<int> const &outer, std::vector<int> const &inner)
{
    std::string s;
    for (int i = 0; i < 5; i++){
        s += std::to_string(outer[i]);
        s += std::to_string(inner[i]);
        s += std::to_string(inner[(i + 1) % 5]);
    }
    return s;
}

int main()
{
    std::string s_max;

    std::vector<bool> positions(10);
    std::fill(positions.end() - 5, positions.end(), true);
    do {
        std::vector<int> outer, inner;
        for (int i = 0; i < positions.size(); i++)
            (!positions[i] ? outer : inner).emplace_back(i + 1);

        do
        {
            std::vector<int> _inner(inner);
            do
            {
                if (is_magic(outer, _inner))
                {
                    std::string s = get_string(outer, _inner);
                    if (s.length() == 16)
                        s_max = std::max(s_max, s);
                }
            } while (std::next_permutation(_inner.begin(), _inner.end()));
        } while (std::next_permutation(outer.begin() + 1, outer.end()));
    } while (std::next_permutation(positions.begin(), positions.end()));

    std::cout << s_max;
}
