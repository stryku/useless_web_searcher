#pragma once

#include "common/string_view.hpp"

#include <fstream>

namespace usl::common::fs
{
    class file_creator
    {
    public:
        explicit file_creator(string_view path)
        {
            std::ofstream{ path };
        }
    };
}
