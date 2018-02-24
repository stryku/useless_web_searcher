#include "index/indexer/site_data_parser.hpp"
#include "index/indexer/parsed_site_data.hpp"


#include <boost/algorithm/string.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <sstream>

namespace usl::index::indexer
{
    parsed_site_data site_data_parser::parse(boost::property_tree::ptree& tree) const
    {
        parsed_site_data parsed;

        parsed.id = extract_id(tree);
        parsed.referenced_urls = extract_referenced_urls(tree);
        parsed.sentences = extract_sentences(tree);

        return parsed;
    }

    common::db::url_id_t site_data_parser::extract_id(boost::property_tree::ptree &tree) const
    {
        return tree.get<common::db::url_id_t>("id");
    }

    std::unordered_set<common::db::url_id_t>
    site_data_parser::extract_referenced_urls(boost::property_tree::ptree &tree) const
    {
        std::unordered_set<common::db::url_id_t> urls;

        for(auto& [name, url] : tree.get_child("referenced_urls"))
        {
            urls.insert(std::stoul(url.data()));
        }

        return urls;
    }

    std::vector<std::vector<std::string>> site_data_parser::extract_sentences(boost::property_tree::ptree &tree) const
    {
        std::vector<std::vector<std::string>> sentences;

        for(auto& [name, sentence_child] : tree.get_child("sentences"))
        {
            std::vector<std::string> sentence;
            auto sentence_str = std::string{ sentence_child.data() };
            boost::split(sentence, sentence_str, ::isspace);
            sentences.emplace_back(std::move(sentence));
        }

        return sentences;
    }
}

