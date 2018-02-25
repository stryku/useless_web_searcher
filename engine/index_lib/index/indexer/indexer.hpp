#pragma once

#include <boost/property_tree/ptree.hpp>

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

        class content_indexer;

        class indexer
        {
        public:
            explicit indexer(page_rank::page_rank& page_rank, content_indexer& content_indexer);

            // Accepts json: { url: id, referenced_urls: { url: id, url: id... }, sentences [ sentence, sentence... ] }
            void index(boost::property_tree::ptree& site_data);

        private:
            void update_ranks(const parsed_site_data &site_data) const;

        private:
            page_rank::page_rank& m_page_rank;
            content_indexer& m_content_indexer;
        };
    }
}
