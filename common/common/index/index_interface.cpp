#include "common/index/index_interface.hpp"

#include "common/index/request_keys.hpp"

#include <boost/algorithm/string/join.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <sstream>

namespace usl::common::index
{

    index_interface::index_interface(const std::string &index_address )
        : common::communication::server::server_interface{ index_address }
    {}

    std::string index_interface::process_sentences(const std::vector<std::vector<std::string>> &sentences,
                                                   const std::unordered_set<common::db::url_id_t> &extracted_urls,
                                                   common::db::url_id_t id)
    {
        const auto formatted_msg = format_process_sentences_msg(sentences, extracted_urls, id);
        return send_and_recv(formatted_msg);
    }

    std::string index_interface::format_process_sentences_msg(const std::vector<std::vector<std::string>> &sentences,
                                                              const std::unordered_set<common::db::url_id_t> &extracted_urls,
                                                              common::db::url_id_t id) const
    {
        std::ostringstream oss;
        boost::property_tree::ptree tree;

        tree.put("type", request_keys::k_process_sentences);
        tree.put("site_content.id", id);

        for(const auto& sentence : sentences)
        {
            const auto joined_sentence = boost::algorithm::join(sentence, " ");
            tree.add("site_content.sentences.sentence", std::move(joined_sentence));
        }

        for(const auto& url_id : extracted_urls)
        {
            tree.add("site_content.referenced_urls.url", url_id);
        }

        boost::property_tree::write_json(oss, tree);
        return oss.str();
    }

    index_interface::get_results_result index_interface::get_results(const std::vector<std::string> &words)
    {
        const auto formatted_msg = format_get_results(words);
        const auto index_result = send_and_recv(formatted_msg);

        std::istringstream iss{ index_result };
        boost::property_tree::ptree tree;
        boost::property_tree::read_json(iss, tree);

        get_results_result results;

        for(const auto& [_, url_id_and_rank] : tree.get_child("ranks"))
        {
            const auto id = url_id_and_rank.get<common::db::url_id_t>("url_id");
            const auto rank = url_id_and_rank.get<double>("rank");
            results[id] = rank;
        }

        return results;
    }

    std::string index_interface::format_get_results(const std::vector<std::string> &words) const
    {
        std::ostringstream oss;
        boost::property_tree::ptree tree;

        tree.put("type", request_keys::k_get);

        for(const auto& word : words)
        {
            tree.add("words.word", word);
        }

        boost::property_tree::write_json(oss, tree);
        return oss.str();
    }
}
