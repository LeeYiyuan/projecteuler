#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "io_util.h"
#include "string_util.h"

int main()
{
    std::string names_string = util::read_file("022_names.txt");
    std::vector<std::string> names = util::split(names_string, ',');
    for (std::string &name : names)
        name = name.substr(1, name.length() - 2);
    std::sort(names.begin(), names.end());

    int total_score = 0;
    for (int i = 0; i < names.size(); i++)
    {
        std::string name = names[i];
        int score = 0;
        for (char &c : name)
            score += (c - 'A') + 1;
        score *= (i + 1);
        total_score += score;
    }

    std::cout << total_score;
}
