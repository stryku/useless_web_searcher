#pragma once

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include <fstream>

namespace usl::common::fs
{
    class file_creator
    {
    public:
        explicit file_creator(const std::string& path)
        {
            const auto dirs = boost::filesystem::path{ path }.parent_path();
            boost::filesystem::create_directories(dirs);
            std::ofstream{ path, std::ios::app };
        }
    };
}
