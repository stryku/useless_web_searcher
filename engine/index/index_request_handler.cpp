#include "index_request_handler.hpp"

#include "common/index/request_keys.hpp"

#include "index/getter/results_getter.hpp"
#include "index/indexer/indexer.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <easylogging/easylogging++.h>

#include <sstream>

namespace usl::index
{
    index_request_handler::index_request_handler(indexer::indexer &indexer, getter::results_getter& results_getter)
        : m_indexer{ indexer }
        , m_results_getter{ results_getter }
    {}

    zmq::message_t index_request_handler::handle(const zmq::message_t &req)
    {
        const auto str_req = std::string{ req.data<const char>(), req.size() };
        std::istringstream iss{ str_req };

        boost::property_tree::ptree tree;
        boost::property_tree::read_json(iss, tree);

        const auto msg_type = tree.get<std::string>("type");
        if(msg_type == common::index::request_keys::k_process_sentences)
        {
            return handle_process_sentences(tree);
        }
        if(msg_type == common::index::request_keys::k_process_sentences)
        {
            return handle_get(tree);
        }

        return zmq::message_t();
    }

    zmq::message_t index_request_handler::handle_process_sentences(boost::property_tree::ptree &parsed_request)
    {
        LOG(INFO) << "index_request_handler handling process_sentences";
        m_indexer.index(parsed_request.get_child("site_content"));
        return zmq::message_t();
    }

    zmq::message_t index_request_handler::handle_get(boost::property_tree::ptree &parsed_request)
    {
        LOG(INFO) << "index_request_handler handling process_sentences";
        std::vector<std::string> words;

        for(auto& [name, word] : parsed_request.get_child("words"))
        {
            words.push_back(word.data());
        }

        const auto ranks = m_results_getter.get_results(words);

        boost::property_tree::ptree tree;

        for(auto& [id, rank] : ranks)
        {
            boost::property_tree::ptree rank_tree;
            rank_tree.put("rank.url", id);
            rank_tree.put("rank.value", rank);

            tree.add_child("ranks.rank", rank_tree);
        }

        std::ostringstream oss;
        boost::property_tree::write_json(oss, tree);
        const auto str_resp = oss.str();
        return zmq::message_t{ std::cbegin(str_resp), std::cend(str_resp) };
    }
}
