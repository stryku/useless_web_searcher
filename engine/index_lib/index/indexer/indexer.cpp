#include "index/indexer/indexer.hpp"
#include "index/indexer/parsed_site_data.hpp"
#include "index/indexer/site_data_parser.hpp"
#include "index/page_rank/page_rank.hpp"

namespace usl::index::indexer
{
    indexer::indexer(page_rank::page_rank &page_rank)
        : m_page_rank{ page_rank }
    {}

    void indexer::index(const std::string &site_data)
    {
        const auto parsed_site_data = site_data_parser{}.parse(site_data);
    }

    void indexer::update_ranks(const parsed_site_data &site_data) const
    {
        for(const auto& referenced_url : site_data.referenced_urls)
        {
            m_page_rank.new_page_reference(referenced_url);
        }
    }
}
