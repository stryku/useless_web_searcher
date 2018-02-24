#pragma once

#include "common/db/url_id.hpp"

#include <string>

namespace usl::parser::data
{
    struct parse_data
    {
        const std::string url;
        const std::string site_content;
        const common::db::url_id_t id;
    };
}
