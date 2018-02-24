#include "index/indexer/indexer.hpp"
#include "index/indexer/parsed_site_data.hpp"
#include "index/indexer/site_data_parser.hpp"

namespace usl::index::indexer
{
    void indexer::index(const std::string &site_data)
    {
        const auto parsed_site_data = site_data_parser{}.parse(site_data);
    }
}