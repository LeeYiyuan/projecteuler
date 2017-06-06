#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "io_util.h"
#include "string_util.h"

int main()
{
    std::string words_string = util::read_file("042_words.txt");
    std::vector<std::string> words = util::split(words_string, ',');
    for (std::string &word : words)
        word = word.substr(1, word.length() - 2);

    int count = 0;
    for (std::string &word : words)
    {
        int value = 0;
        for (char &c : word)
            value += c - 'A' + 1;
        int x = 2 * value;
        double n = (-1 + std::sqrt(1 + 4 * x)) / 2;
        if (int(n) == n)
            count++;
    }

    std::cout << count;
}
