#pragma once

#include "common/db/url_id.hpp"

#include "index/page_rank/page_rank_storage.hpp"

namespace usl::index::page_rank
{
    class page_rank
    {
    public:
        explicit page_rank(const std::string& working_directory);

        void new_page_reference(common::db::url_id_t id);
        double get_rank(common::db::url_id_t id) const;

    private:
        page_rank_storage m_page_rank_storage;
    };
}
