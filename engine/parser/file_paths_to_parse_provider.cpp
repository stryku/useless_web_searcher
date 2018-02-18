#include "file_paths_to_parse_provider.hpp"
#include "common/communication/context.hpp"

#include <easylogging/easylogging++.h>
#include <thread>

namespace usl::parser::poller
{
    file_paths_to_parse_provider::file_paths_to_parse_provider()
        : m_socket{ common::communication::context, ZMQ_REQ }
    {}

    void file_paths_to_parse_provider::run(const std::string& parse_frontier_address, content::content_parser& parser)
    {
        LOG(INFO) << "Connecting to: " << parse_frontier_address;
        m_socket.connect(parse_frontier_address);
        zmq::message_t request;

        while(true)
        {
            LOG(INFO) << "Sending request";
            m_socket.send (request);

            zmq::message_t reply;
            m_socket.recv (&reply);
            LOG(INFO) << "Received: " << static_cast<const char*>(reply.data()) << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds{5});
        }
    }
}

