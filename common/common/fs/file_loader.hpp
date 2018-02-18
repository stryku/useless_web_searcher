#pragma once

#include <boost/filesystem.hpp>

#include <vector>
#include <cstdint>
#include <string>
#include <fstream>

namespace usl::common::fs
{
    class file_loader
    {
    public:
        template <typename Buffer>
        Buffer load(const std::string& path) const
        {
            Buffer buffer;

            if(boost::filesystem::exists(path))
            {
                std::ifstream t(path, std::ios::binary);
                t.seekg(0, std::ios::end);
                const auto size = t.tellg();
                buffer.resize(size);
                t.seekg(0);
                t.read(reinterpret_cast<char*>(&buffer[0]), size);
            }

            return buffer;
        }
    };
}
