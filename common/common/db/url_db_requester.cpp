#include "common/db/url_db_requester.hpp"

namespace usl::common::db
{
    url_db_requester::url_db_requester(const std::string& db_address)
        : m_socket{ communication::context, ZMQ_REQ }
    {
        LOG(INFO) << "url_db_requester connecting to: " << db_address;
        m_socket.connect(db_address);
    }

    std::string url_db_requester::insert(const std::string &url)
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

    std::string url_db_requester::get(size_t id)
    {
        LOG(INFO) << "url_db_requester get: " << id;

        boost::property_tree::ptree tree;
        tree.put("type", "get");
        tree.put("url", id);

        std::ostringstream oss;
        boost::property_tree::write_json(oss, tree);

        const auto str_msg = oss.str();

        zmq::message_t msg{ str_msg.begin(), str_msg.end() };

        LOG(INFO) << "url_db_requester get sending request: " << str_msg;
        m_socket.send(msg);

        LOG(INFO) << "url_db_requester get recv...";
        zmq::message_t reply;
        m_socket.recv (&reply);

        const auto str_reply = std::string{ reply.data<char>(), reply.size() };
        LOG(INFO) << "url_db_requester get received: " << str_reply;

        return str_reply;
    }
}
