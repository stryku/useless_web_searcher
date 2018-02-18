#pragma once

#include "common/string_view.hpp"

#include "url_db/db_entry_view.hpp"
#include "url_db/url_db_offset.hpp"
#include "url_db/url_db_storage.hpp"

#include <boost/optional.hpp>

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

        const db_entry_view& get(id_t id) const;

        void insert(const std::string& url);

    private:
        friend class url_db_loader;

        std::unordered_map<id_t, offset_t> m_id_to_offset;
        std::unordered_set<url_t> m_urls;

        url_db_storage m_storage;
    };
}
