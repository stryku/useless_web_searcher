#pragma once

#include <vector>
#include <cstdint>
#include <string>

namespace usl::common::fs
{
    class file_loader
    {
    public:
        std::string load_string(const std::string& path) const;
    };
}
