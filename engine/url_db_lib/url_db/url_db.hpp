#pragma once

#include "common/db/url_id.hpp"
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
        using url_t = std::string;

        explicit url_db(url_db_storage& storage);

        const db_entry_view& get(common::db::url_id_t id) const;
        db_entry_view& get(common::db::url_id_t id);
        common::db::url_id_t insert(const std::string& url);
        boost::optional<db_entry_to_process> get_for_processing();
        void update_state_as_processed(common::db::url_id_t id);

    private:
        friend class url_db_loader;

        std::unordered_map<common::db::url_id_t, offset_t> m_id_to_offset;
        std::unordered_map<url_t, common::db::url_id_t> m_url_to_id;
        std::unordered_set<url_t> m_urls;
        std::queue<common::db::url_id_t> m_not_processed;

        url_db_storage& m_storage;
    };
}
