#pragma once

#include "common/string_view.hpp"

#include "url_db/db_entry_view.hpp"
#include "url_db/url_db_offset.hpp"

#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <string>

namespace usl::url_db
{
    class url_db_loader;

    class url_db
    {
    public:
        using id_t = uint64_t;
        using url_t = std::string;

    private:
        friend class url_db_loader;

        std::unordered_map<id_t, offset_t> m_id_to_offset;
        std::unordered_set<url_t> m_urls;
    };
}
