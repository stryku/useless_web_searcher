#include "common/communication/server/server_interface.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <easylogging/easylogging++.h>

namespace usl::common::communication::server
{
    server_interface::server_interface(const std::string& db_address)
        : m_socket{ communication::context, ZMQ_REQ }
    {
        LOG(INFO) << "server_interface connecting to: " << db_address;
        m_socket.connect(db_address);
    }

    std::string server_interface::send_and_recv(const std::string &type,
                                                const std::string &field,
                                                const std::string &field_value)
    {
        LOG(INFO) << "server_interface " << type;

        boost::property_tree::ptree tree;
        tree.put("type", type);
        tree.put(field, field_value);

        std::ostringstream oss;
        boost::property_tree::write_json(oss, tree);

        return send_and_recv(oss.str());
    }

    std::string server_interface::send_and_recv(const std::string &str_msg)
    {
        zmq::message_t msg{ str_msg.begin(), str_msg.end() };
        m_socket.send(msg);

        zmq::message_t reply;
        m_socket.recv (&reply);

        return std::string{ reply.data<char>(), reply.size() };
    }
}
