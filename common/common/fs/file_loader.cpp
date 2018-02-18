#include "common/fs/file_loader.hpp"

#include <fstream>

namespace usl::common::fs
{
    std::vector<uint8_t > file_loader::load(const std::string& path) const
    {
        std::ifstream t(path, std::ios::binary);
        t.seekg(0, std::ios::end);
        const auto size = t.tellg();
        std::vector<uint8_t> buffer(size);
        t.seekg(0);
        t.read(reinterpret_cast<char*>(&buffer[0]), size);
        return buffer;
    }
}
