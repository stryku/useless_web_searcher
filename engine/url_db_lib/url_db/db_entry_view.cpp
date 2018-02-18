#include <cstring>
#include "db_entry_view.hpp"

namespace usl::url_db
{
    std::vector<uint8_t> db_entry_view::to_binary() const
    {
        std::vector<uint8_t> result;

        result.push_back(status);

        auto url_ptr = url();

        while(*url_ptr)
        {
            result.push_back(static_cast<uint8_t>(*url_ptr));
            ++url_ptr;
        }

        return result;
    }

    const char* const db_entry_view::url() const
    {
        return &url_begin;
    }

    size_t db_entry_view::size() const
    {
        //status_size + url_length + null
        return 1u + std::strlen(url()) + 1u;
    }
}
