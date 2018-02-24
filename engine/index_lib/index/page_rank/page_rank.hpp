#pragma once

#include "common/db/url_id.hpp"

namespace usl::index::page_rank
{
    class page_rank
    {
    public:
        void new_page_reference(common::db::url_id_t id);
    };
}
