/*
    Each digit appearing in keylog.txt must appear in the required number at
    least once. It is possible that the hit with the least possible length is
    one where each digit appears exactly once.

    Luckily it appears than this is the case for the required answer.

    If needed, we can consider permutations of the digits appearing in
    keylog.txt and try permutations with repeated digits until we find an
    answer, though I am not sure how fast this takes (surely faster than naively
    searching through the integers.)
*/

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "io_util.h"
#include "string_util.h"

bool check_key(std::vector<int> const &permutation, std::vector<int> const &key)
{
    for (int i = 0; i < permutation.size(); i++)
    {
        if (permutation[i] != key[0])
            continue;
        for (int j = i + 1; j < permutation.size(); j++)
        {
            if (permutation[j] != key[1])
                continue;
            for (int k = j + 1; k < permutation.size(); k++)
            {
                if (permutation[k] != key[2])
                    continue;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    std::string keys_string = util::read_file("079_keylog.txt");
    std::vector<std::string> key_strings = util::split(keys_string, '\n');
    std::vector<std::vector<int>> keys;
    for (std::string &key_string : key_strings)
        keys.emplace_back(std::vector<int>({ key_string[0] - '0', key_string[1] - '0', key_string[2] - '0' }));

    std::vector<int> digits;
    for (std::vector<int> &key : keys)
        for (int &digit : key)
            if (std::find(digits.begin(), digits.end(), digit) == digits.end())
                digits.emplace_back(digit);

    do
    {
        bool is_hit = true;
        for (std::vector<int> &key : keys)
        {
            if (!check_key(digits, key))
            {
                is_hit = false;
                break;
            }
        }
        if (is_hit)
        {
            for (int &digit : digits)
                std::cout << (char)(digit + '0');
            return 0;
        }
    } while (std::next_permutation(digits.begin(), digits.end()));
}
