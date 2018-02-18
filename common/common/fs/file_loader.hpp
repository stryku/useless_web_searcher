#pragma once

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
        Buffer load(const std::string& path)
        {
            std::ifstream t(path, std::ios::binary);
            t.seekg(0, std::ios::end);
            const auto size = t.tellg();
            Buffer buffer;
            buffer.resize(size);
            t.seekg(0);
            t.read(reinterpret_cast<char*>(&buffer[0]), size);
            return buffer;
        }
    };
}
