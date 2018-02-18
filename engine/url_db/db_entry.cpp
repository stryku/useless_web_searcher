#include "db_entry.hpp"

namespace usl::url_db
{
    std::vector<uint8_t> db_entry::to_binary() const
    {
        std::vector<uint8_t> result;

        result.push_back(status);

        auto url_ptr = url;

        while(*url_ptr)
        {
            result.push_back(static_cast<uint8_t>(*url_ptr));
            ++url_ptr;
        }

        return result;
    }
}
