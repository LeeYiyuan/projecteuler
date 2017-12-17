/*
    First we cache pairs of words that are anagrams of each other.

    Next, we cache squares that have length up to the maximum of the words in
    the word pairs.

    Then for each word pair (A, B) where len(A) = len(B) = k, we consider
    squares of k digits. We define mapping getNumber such that getNumber((A, B),
    square) substitutes the digits of A with the corresponding digits of the
    square number, and then retrieves the number corresponding to B based on the
    substituted digits and returns this result.

    For every square such that square' = getNumber((A, B), square) is also a k
    digit square, we collect max(square, square') and at the end, output the
    highest collected value.
*/

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <utility>
#include <cmath>
#include <cstdint>
#include "io_util.h"
#include "string_util.h"

int64_t get_number(std::pair<std::string, std::string> const &p, int64_t n_A)
{
    std::unordered_map<char, int> letter_to_digit;
    for (int i = 0; i < p.first.length(); i++)
    {
        char letter = p.first[i];
        int digit = std::to_string(n_A)[i] - '0';
        auto it_letter = letter_to_digit.find(letter);
        if (it_letter != letter_to_digit.end())
        {
            if (digit != it_letter->second)
                return -1;
        }
        else if (std::find_if(letter_to_digit.begin(), letter_to_digit.end(),
            [&digit](auto &kv){
                return kv.second == digit;
            }) != letter_to_digit.end())
        {
            return -1;
        }
        letter_to_digit[letter] = digit;
    }
    std::string result = "";
    for (char const &letter : p.second)
        result += letter_to_digit[letter] + '0';
    return std::stoll(result);
}

int main()
{
    std::string words_string = util::read_file("098_words.txt");
    std::vector<std::string> words = util::split(words_string, ',');
    for(std::string &word : words)
        word = word.substr(1, word.length() - 2);

    // Get word anagram pairs.
    int max_word_length = -1;
    std::vector<std::pair<std::string, std::string>> pairs;
    for (int i_a = 0; i_a < words.size(); i_a++)
    {
        std::string a = words[i_a];
        for (int i_b = i_a + 1; i_b < words.size(); i_b++)
        {
            std::string b = words[i_b];
            if (a.length() == b.length() && std::is_permutation(a.begin(), a.end(), b.begin()))
            {
                pairs.emplace_back(a, b);
                max_word_length = std::max(max_word_length, (int)std::max(a.length(), b.length()));
            }
        }
    }

    std::vector<std::vector<ll>> squares(max_word_length + 1, std::vector<ll>());
    int n = 0;
    double limit = std::pow(10, ((double)max_word_length) / 2);
    while ((++n) < limit)
        squares[std::to_string(n * n).length()].emplace_back(n * n);


    int64_t largest_square = -1;
    for (std::pair<std::string, std::string> &p : pairs)
    {
        int length = p.first.length();
        for (int64_t &square : squares[length])
        {
            int64_t number = get_number(p, square);
            if (number != -1 && std::find(squares[length].begin(), squares[length].end(), number) != squares[length].end())
            {
                largest_square = std::max(largest_square, std::max(square, number));
            }
        }
    }

    std::cout << largest_square;
}
