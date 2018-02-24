#include "index/indexer/indexer.hpp"
#include "index/indexer/parsed_site_data.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <sstream>

namespace usl::index::indexer
{
    void indexer::index(const std::string &site_data)
    {

    }

    parsed_site_data indexer::parse_site_data(const std::string &site_data) const
    {
        std::istringstream iss(site_data);

        boost::property_tree::ptree tree;
        boost::property_tree::read_json(iss, tree);

        parsed_site_data parsed;

        parsed.id = tree.get<common::db::url_id_t>("id");

        for(auto& [name, url] : tree.get_child("referenced_urls"))
        {
            parsed.referenced_urls.insert(std::stoul(url.data()));
        }




        return parsed_site_data();
    }
}