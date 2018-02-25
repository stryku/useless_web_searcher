#pragma once

#include "common/db/url_id.hpp"

#include <string>
#include <unordered_set>
#include <vector>

namespace usl::index::indexer
{
    struct parsed_site_data
    {
        common::db::url_id_t id;
        std::unordered_set<common::db::url_id_t> referenced_urls;
        std::vector<std::vector<std::string>> sentences;
    };
}
