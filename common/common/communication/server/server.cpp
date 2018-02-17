#include "common/communication/server/server.hpp"

namespace usl::common::communication::server
{
    server::server(zmq::context_t& context)
        : m_socket{ context, ZMQ_REP }
    {}

    void server::bind(std::experimental::string_view bind_address)
    {
        m_socket.bind(bind_address.data());
    }

    void server::run()
    {
        while (true)
        {
            zmq::message_t request;
            m_socket.recv (&request);

            zmq::message_t reply (5);
            memcpy (reply.data (), "World", 5);
            socket.send (reply);
        }

    }
}

