#pragma once

#include <vector>
#include <cstdint>
#include <string>

namespace usl::common::fs
{
    class file_loader
    {
    public:
        std::vector<uint8_t> load(const std::string& path) const;
    };
}
