#include "index/indexer/site_data_parser.hpp"
#include "index/indexer/parsed_site_data.hpp"

#include <boost/property_tree/json_parser.hpp>

#include <sstream>

namespace usl::index::indexer
{
    parsed_site_data site_data_parser::parse(const std::string &site_data) const
    {
        std::istringstream iss(site_data);

        boost::property_tree::ptree tree;
        boost::property_tree::read_json(iss, tree);

        parsed_site_data parsed;

        parsed.id = extract_id(tree);

        for(auto& [name, url] : tree.get_child("referenced_urls"))
        {
            parsed.referenced_urls.insert(std::stoul(url.data()));
        }




        return parsed_site_data();
    }

    common::db::url_id_t site_data_parser::extract_id(boost::property_tree::ptree &tree) const
    {
        return tree.get<common::db::url_id_t>("id");
    }
}

