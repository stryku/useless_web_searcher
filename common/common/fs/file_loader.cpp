#include "common/fs/file_loader.hpp"

#include <fstream>

namespace usl::common::fs
{
    std::string file_loader::load_string(const std::string& path) const
    {
        std::ifstream t(path, std::ios::binary);
        t.seekg(0, std::ios::end);
        const auto size = t.tellg();
        std::string buffer;
        buffer.resize(size);
        t.seekg(0);
        t.read(&buffer[0], size);
        return buffer;
    }
}
