#include "io_util.h"
#include <string>
#include <fstream>
#include <streambuf>

std::string util::read_file(std::string file_name)
{
    std::ifstream t(file_name);
    return std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
}
