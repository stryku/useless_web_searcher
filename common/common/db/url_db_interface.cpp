#include "common/db/url_db_interface.hpp"
#include "common/db/url_db_request_keys.hpp"

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
        return send_and_recv(common::db::request_keys::k_insert, "url", url);
    }

    std::string url_db_interface::get(common::db::url_id_t id)
    {
        return send_and_recv(common::db::request_keys::k_get, "id", id);
    }

    std::string url_db_interface::update_state_as_processed(common::db::url_id_t id)
    {
        return send_and_recv(common::db::request_keys::k_update_state_as_processed, "id", id);
    }

    std::string url_db_interface::send_and_recv(const std::string &type,
                                                const std::string &field,
                                                const std::string &field_value)
    {
        LOG(INFO) << "url_db_interface " << type << " " << field_value;

        boost::property_tree::ptree tree;
        tree.put("type", type);
        tree.put(field, field_value);

        std::ostringstream oss;
        boost::property_tree::write_json(oss, tree);

        const auto str_msg = oss.str();

        zmq::message_t msg{ str_msg.begin(), str_msg.end() };
        m_socket.send(msg);

        zmq::message_t reply;
        m_socket.recv (&reply);

        return std::string{ reply.data<char>(), reply.size() };
    }
}
