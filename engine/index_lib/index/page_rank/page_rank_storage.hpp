#pragma once

#include "common/db/url_id.hpp"

namespace usl::index::page_rank
{
    struct page_rank_entry;

    class page_rank_storage
    {
    public:
        void update(common::db::url_id_t id, double rank);
    };
}