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
#include <queue>

namespace usl::url_db
{
    class url_db_loader;
    class db_entry_to_process;

    class url_db
    {
    public:
        enum class state_type : uint8_t
        {
            not_processed,
            processing,
            processed
        };

        using id_t = uint64_t;
        using url_t = std::string;

        const db_entry_view& get(id_t id) const;
        db_entry_view& get(id_t id);
        void insert(const std::string& url);
        boost::optional<db_entry_to_process> get_for_processing();

    private:
        friend class url_db_loader;

        std::unordered_map<id_t, offset_t> m_id_to_offset;
        std::unordered_set<url_t> m_urls;
        std::queue<id_t> m_not_processed;

        url_db_storage m_storage;
    };
}
