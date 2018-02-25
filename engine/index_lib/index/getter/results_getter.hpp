#pragma once

#include "common/db/url_id.hpp"
#include "index/indexer/index_file.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace usl::index
{
    namespace page_rank
    {
        class page_rank;
        struct page_rank_storage_entry;
    }

    namespace getter
    {
        class results_getter
        {
        public:
            explicit results_getter(page_rank::page_rank& page_rank, const std::string& indexes_dir);

            std::unordered_map<common::db::url_id_t, double> get_results(const std::vector<std::string>& words);

        private:
            void get_for_words(const std::vector<std::string>& words,
                               size_t count,
                               std::vector<indexer::index_file::index_file_entry>& hits);
            
        private:
            page_rank::page_rank& m_page_rank;
            const std::string m_indexes_dir;
        };
    }
}
