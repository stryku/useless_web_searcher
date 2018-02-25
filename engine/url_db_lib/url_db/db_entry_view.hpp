#pragma once

#include "common/db/url_state.hpp"
#include <cstdint>
#include <vector>
#include <cstddef>

namespace usl::url_db
{
#pragma pack(1)
    struct db_entry_view
    {
        uint8_t status;
        char url_begin;

        std::vector<uint8_t> to_binary() const;
        const char* const url() const;
        size_t size() const;
    };
#pragma pack()
}
