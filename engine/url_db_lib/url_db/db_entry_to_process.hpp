#pragma once

#include "url_db/url_db.hpp"

namespace usl::url_db
{
    struct db_entry_to_process
    {
        url_db::id_t id;
        std::string url;
    };
}
