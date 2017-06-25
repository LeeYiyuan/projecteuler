#pragma once

#include <string>
#include <vector>

namespace util
{
    std::string replace(std::string const &s, std::string const &c, std::string const &cn);

    std::vector<std::string> split(std::string const &s, char delim);

    bool is_palindrome(std::string const &s);
}
