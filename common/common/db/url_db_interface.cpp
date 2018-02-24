#include "common/db/url_db_interface.hpp"

namespace usl::common::db
{
    url_db_interface::url_db_interface(const std::string& db_address)
        : m_socket{ communication::context, ZMQ_REQ }
    {
        LOG(INFO) << "url_db_interface connecting to: " << db_address;
        m_socket.connect(db_address);
    }

    std::string url_db_interface::insert(const std::string &url)
    {
        LOG(INFO) << "url_db_interface insert: " << url;

        boost::property_tree::ptree tree;
        tree.put("type", "insert");
        tree.put("url", url);

        std::ostringstream oss;
        boost::property_tree::write_json(oss, tree);

        const auto str_msg = oss.str();

        zmq::message_t msg{ str_msg.begin(), str_msg.end() };

        m_socket.send(msg);

        zmq::message_t reply;
        m_socket.recv (&reply);

        const auto str_reply = std::string{ reply.data<char>(), reply.size() };

        return str_reply;
    }

    std::string url_db_interface::get(common::db::url_id_t id)
    {
        LOG(INFO) << "url_db_interface get: " << id;

        boost::property_tree::ptree tree;
        tree.put("type", "get");
        tree.put("url", id);

        std::ostringstream oss;
        boost::property_tree::write_json(oss, tree);

        const auto str_msg = oss.str();

        zmq::message_t msg{ str_msg.begin(), str_msg.end() };
        m_socket.send(msg);

        zmq::message_t reply;
        m_socket.recv (&reply);

        const auto str_reply = std::string{ reply.data<char>(), reply.size() };

        return str_reply;
    }

    std::string url_db_interface::update_state_as_processed(common::db::url_id_t id)
    {
        LOG(INFO) << "url_db_interface update_state_as_processed: " << id;

        boost::property_tree::ptree tree;
        tree.put("type", "update_state_as_processed");
        tree.put("url", id);

        std::ostringstream oss;
        boost::property_tree::write_json(oss, tree);

        const auto str_msg = oss.str();

        zmq::message_t msg{ str_msg.begin(), str_msg.end() };
        m_socket.send(msg);

        zmq::message_t reply;
        m_socket.recv (&reply);

        const auto str_reply = std::string{ reply.data<char>(), reply.size() };

        return str_reply;
    }
}
