#pragma once

#include "common/db/url_id.hpp"

#include <string>
#include <vector>

namespace usl::index::indexer
{
    class indexes_storage
    {
    private:
        using word_iterator_t = std::vector<std::string>::const_iterator;

    public:
        explicit indexes_storage(const std::string& working_directory);

        void update(word_iterator_t words_begin, word_iterator_t words_end, common::db::url_id_t id) const;

    private:
        std::string build_index_path(word_iterator_t words_begin, word_iterator_t words_end) const;
        std::string::size_type predict_path_size(word_iterator_t words_begin, word_iterator_t words_end) const;

        const std::string m_indexes_dir;
    };
}
