#pragma once

#include <cstdint>
#include <vector>

namespace usl::url_db
{
    class db_entry
    {
        uint8_t status;
        const char* url;

        std::vector<uint8_t> to_binary() const;
    };
}
