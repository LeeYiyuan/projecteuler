/*
    First we convert from Roman numerals to decimal.

    Then we convert from decimal to the shortest Roman numeral.

    Then for each conversion we count how many characters we save, and sum up
    all savings for our answer.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "io_util.h"
#include "string_util.h"

int main()
{
    std::string numerals_string = util::read_file("089_roman.txt");
    std::vector<std::string> numerals = util::split(numerals_string, '\n');

    std::vector<int> decimals;
    std::unordered_map<char, int> values = {
        { 'I', 1 },
        { 'V', 5 },
        { 'X', 10 },
        { 'L', 50 },
        { 'C', 100 },
        { 'D', 500 },
        { 'M', 1000 }
    };

    for (std::string &numeral : numerals)
    {
        int decimal = 0;
        int i = 0;
        while (i < numeral.size())
        {
            int value = values[numeral[i]];
            if (i < numeral.size() - 1 && value < values[numeral[i + 1]])
            {
                decimal += values[numeral[i + 1]] - value;
                i++; // Skip next character.
            }
            else
            {
                decimal += value;
            }
            i++;
        }
        decimals.emplace_back(decimal);
    }

    std::vector<std::string> hundreds_numeral = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
    std::vector<std::string> tens_numeral = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
    std::vector<std::string> ones_numeral = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

    std::vector<std::string> shortest_numerals;
    for (int &decimal : decimals)
    {
        std::string numeral = "";

        int thousands = decimal / 1000;
        for (int i = 0; i < thousands; i++)
            numeral += 'M';

        numeral += hundreds_numeral[(decimal / 100) % 10];
        numeral += hundreds_numeral[(decimal / 10) % 10];
        numeral += hundreds_numeral[decimal % 10];

        shortest_numerals.emplace_back(numeral);
    }

    int savings = 0;
    for (int i = 0; i < numerals.size(); i++)
    {
        std::string numeral = numerals[i];
        std::string shortest_numeral = shortest_numerals[i];
        savings += numeral.length() - shortest_numeral.length();
    }

    std::cout << savings;
}
