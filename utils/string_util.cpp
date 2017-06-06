#include "string_util.h"
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <iterator>

std::string util::replace(std::string s, std::string c, std::string cn)
{
    return std::regex_replace(s, std::regex(c), cn);
}

std::vector<std::string> util::split(std::string s, char delim) {
    std::vector<std::string> splitted;
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim))
        splitted.emplace_back(item);
    return splitted;
}

bool util::is_palindrome(std::string s)
{
    std::string s_reversed = s;
    std::reverse(s_reversed.begin(), s_reversed.end());
    return s == s_reversed;
}
