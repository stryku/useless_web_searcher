#pragma once

#include "common/db/url_id.hpp"

namespace usl::url_db
{
    struct db_entry_to_process
    {
        common::db::url_id_t id;
        std::string url;
    };
}
