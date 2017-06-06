#pragma once

#include <string>
#include <vector>

namespace util
{
    std::string replace(std::string s, std::string c, std::string cn);

    std::vector<std::string> split(std::string s, char delim);

    bool is_palindrome(std::string s);
}
