#pragma once

#include <string>

namespace usl::index
{
    namespace page_rank
    {
        class page_rank;
    }

    namespace indexer
    {
        struct parsed_site_data;

        class indexer
        {
        public:
            explicit indexer(page_rank::page_rank& pr);

            // Accepts json: { url: id, referenced_urls: { url: id, url: id... }, sentences [ sentence, sentence... ] }
            void index(const std::string &site_data);

        private:
            void update_ranks(const parsed_site_data &site_data) const;
            void index_content(const parsed_site_data &site_data) const;

        private:
            page_rank::page_rank& m_page_rank;
        };
    }
}
