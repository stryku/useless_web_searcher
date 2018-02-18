#pragma once

#include "common/communication/context.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <easylogging/easylogging++.h>

#include <zmq.hpp>

#include <string>
#include <sstream>

namespace usl::common::db
{
    class url_db_requester
    {
    public:
        explicit url_db_requester(const std::string& db_address)
            : m_socket{ communication::context, ZMQ_REQ }
        {
            LOG(INFO) << "url_db_requester connecting to: " << db_address;
            m_socket.connect(db_address);
        }

        std::string insert(const std::string& url)
        {
            LOG(INFO) << "url_db_requester insert: " << url;


            boost::property_tree::ptree tree;
            tree.put("type", "insert");
            tree.put("url", url);

            std::ostringstream oss;
            boost::property_tree::write_json(oss, tree);

            const auto str_msg = oss.str();

            zmq::message_t msg{ str_msg.begin(), str_msg.end() };

            LOG(INFO) << "url_db_requester insert sending request: " << str_msg;
            m_socket.send(msg);

            LOG(INFO) << "url_db_requester insert recv...";
            zmq::message_t reply;
            m_socket.recv (&reply);

            const auto str_reply = std::string{ reply.data<char>(), reply.size() };
            LOG(INFO) << "url_db_requester insert received: " << str_reply;

            return str_reply;
        }

    private:
        zmq::socket_t m_socket;
    };
}
