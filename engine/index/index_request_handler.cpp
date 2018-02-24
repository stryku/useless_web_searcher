#include "index_request_handler.hpp"

#include "common/index/request_keys.hpp"

#include "index/indexer/indexer.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <easylogging/easylogging++.h>

#include <sstream>

namespace usl::index
{
    index_request_handler::index_request_handler(indexer::indexer &indexer)
        : m_indexer{ indexer }
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
        m_indexer.index(parsed_request.get_child("id"));
        return zmq::message_t();
    }

}
