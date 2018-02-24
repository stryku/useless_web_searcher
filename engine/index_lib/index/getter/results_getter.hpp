#pragma once

#include <string>
#include <vector>

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
            explicit results_getter(page_rank::page_rank& page_rank);

            std::vector<page_rank::page_rank_storage_entry> get_results(const std::vector<std::string>& words);

        private:
            page_rank::page_rank& m_page_rank;
        };
    }
}
