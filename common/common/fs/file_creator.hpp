#pragma once

#include <fstream>

namespace usl::common::fs
{
    class file_creator
    {
    public:
        explicit file_creator(const std::string& path)
        {
            std::ofstream{ path, std::ios::app };
        }
    };
}
