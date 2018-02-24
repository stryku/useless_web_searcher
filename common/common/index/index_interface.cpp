#include "common/index/index_interface.hpp"

#include "common/index/request_keys.hpp"

#include <boost/algorithm/string/join.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <sstream>

namespace usl::common::index
{

    index_interface::index_interface(const std::string &index)
        : common::communication::server::server_interface{ index }
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
}
