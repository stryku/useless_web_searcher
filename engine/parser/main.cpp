#include "parser/parser_lib.hpp"

#include <boost/filesystem.hpp>

#include <iostream>

int main()
{
    std::cout << parser_lib();
    boost::filesystem::temp_directory_path();
}