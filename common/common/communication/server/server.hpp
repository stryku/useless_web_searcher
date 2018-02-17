#pragma once

#include <zmq.hpp>

#include <string>

namespace usl::common::communication::server
{
    class server
    {
    public:
        server(zmq::context_t& context)
          : m_socket{ context, ZMQ_REP }
        {}

        void bind(std::string_view bind_address);

    private:
        zmq::socket_t m_socket;
    };
}