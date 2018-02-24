#pragma once

#include <boost/property_tree/ptree.hpp>

#include <string>
#include <common/db/url_id.hpp>

namespace usl::index::indexer
{
    struct parsed_site_data;

    class site_data_parser
    {
    public:
        parsed_site_data parse(const std::string& site_data) const;

    private:
        common::db::url_id_t extract_id(boost::property_tree::ptree& tree) const;
    };
}
