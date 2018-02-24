#pragma once

#include "common/db/url_id.hpp"

#include <string>
#include <vector>

namespace usl::index::indexer
{
    struct parsed_site_data
    {
        common::db::url_id_t id;
        std::vector<common::db::url_id_t> referenced_urls;
        std::vector<std::vector<std::string>> sentences;
    };
}
