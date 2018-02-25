#pragma once

#include "common/db/url_id.hpp"

#include <boost/property_tree/ptree.hpp>

#include <unordered_set>
#include <string>
#include <vector>

namespace usl::index::indexer
{
    struct parsed_site_data;

    class site_data_parser
    {
    public:
        parsed_site_data parse(boost::property_tree::ptree& tree) const;

    private:
        common::db::url_id_t extract_id(boost::property_tree::ptree& tree) const;
        std::unordered_set<common::db::url_id_t> extract_referenced_urls(boost::property_tree::ptree& tree) const;
        std::vector<std::vector<std::string>> extract_sentences(boost::property_tree::ptree& tree) const;
    };
}
