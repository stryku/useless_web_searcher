#include "common/communication/server/server.hpp"

namespace usl::common::communication::server
{
    server::server(zmq::context_t& context)
        : m_socket{ context, ZMQ_REP }
    {}

    void server::bind(std::string_view bind_address)
    {
        m_socket.bind(bind_address.c_str());
    }
}

