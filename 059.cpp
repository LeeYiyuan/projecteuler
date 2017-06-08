/*
    We loop through the 26^3 = 17576 possible combinations of the key and pass
    the ciphertext through a cyclic XOR mask based on the key.

    We take the key that produces most letters, selecting the 'most English'
    plaintext.

    I also tried doing frequency analysis to get see which key gives a frequency
    vector that is closest to the standard English frequency vector, with
    respect to L_2 norm.

    Surprisingly, there are keys which give frequency vectors that are "more
    English", but the resultant plaintexts has extremely few letters. It turns
    out that these are garbage that happen to, among the few letters they
    produce, sound "more English".
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "io_util.h"
#include "string_util.h"

int main()
{
    std::vector<int> lowercase_range, uppercase_range;

    for (int i = 0b01100001; i <= 0b01111010; i++)
        lowercase_range.emplace_back(i);
    for (int i = 0b01000001; i <= 0b01011010; i++)
        uppercase_range.emplace_back(i);

    std::string ciphertext_string = util::read_file("059_cipher.txt");
    std::vector<int> ciphertext;
    for (std::string &ciphertext_character : util::split(ciphertext_string, ','))
        ciphertext.emplace_back(std::stoi(ciphertext_character));

    int maximum_sum;
    int maximum_letter_count = -1;

    for (int &a : lowercase_range)
    {
        for (int &b : lowercase_range)
        {
            for (int &c : lowercase_range)
            {
                std::vector<int> key = { a, b, c };
                int letter_count = 0;
                int sum = 0;
                for (int i = 0; i < ciphertext.size(); i++)
                {
                    int plain_character = ciphertext[i] ^ key[i % 3];
                    if (std::binary_search(lowercase_range.begin(), lowercase_range.end(), plain_character) ||
                        std::binary_search(uppercase_range.begin(), uppercase_range.end(), plain_character))
                        letter_count++;
                    sum += plain_character;
                }

                if (letter_count > maximum_letter_count)
                {
                    maximum_sum = sum;
                    maximum_letter_count = letter_count;
                }
            }
        }
    }

    std::cout << maximum_sum;
}
