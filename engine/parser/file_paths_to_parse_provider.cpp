#include "file_paths_to_parse_provider.hpp"
#include "common/communication/context.hpp"

#include <easylogging/easylogging++.h>

namespace usl::parser
{
    file_paths_to_parse_provider::file_paths_to_parse_provider(const std::string& parse_frontier_address)
        : m_socket{ common::communication::context, ZMQ_REQ }
    {
        LOG(INFO) << "Connecting to: " << parse_frontier_address;
        m_socket.connect(parse_frontier_address);
    }

    std::string file_paths_to_parse_provider::get()
    {
        zmq::message_t request;

        LOG(INFO) << "Sending request";
        m_socket.send (request);

        zmq::message_t reply;
        m_socket.recv (&reply);
        LOG(INFO) << "Received: " << static_cast<const char*>(reply.data()) << std::endl;
        return std::string{ reply.data<const char>(), reply.size() };
    }
}

