#pragma once

#include "common/db/url_id.hpp"

#include <string>

namespace usl::index::indexer
{
    class index_file
    {
    public:
        explicit index_file(const std::string& path);

        void new_hit(common::db::url_id_t id) const;

    private:
        const std::string m_path;
    };
}