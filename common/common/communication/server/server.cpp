#include "common/communication/server/server.hpp"

#include <boost/assert.hpp>

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
            BOOST_ASSERT_MSG(m_message_handler, "message handler not set");
            const auto request = recv_request();
            auto response = m_message_handler->handle(request);
            m_socket.send(response);
        }

    }

    zmq::message_t server::recv_request()
    {
        zmq::message_t request;
        m_socket.recv (&request);
        return std::move(request);
    }
}

