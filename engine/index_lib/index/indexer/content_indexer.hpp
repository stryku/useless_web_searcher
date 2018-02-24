#pragma once

#include "common/db/url_id.hpp"
#include "index/indexer/indexes_storage.hpp"

#include <string>
#include <vector>

namespace usl::index::indexer
{
    class parsed_site_data;

    class content_indexer
    {
    public:
        explicit content_indexer(const std::string& working_directory);

        void index(const parsed_site_data& site_data) const;

    private:
        void index_sentence(const std::vector<std::string>& sentence, common::db::url_id_t id) const;
        void index_words(const std::vector<std::string>& sentence,
                         size_t words_count,
                         common::db::url_id_t id) const;

    private:
        indexes_storage m_indexes_storage;
    };
}