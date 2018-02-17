#pragma once

#include "common/communication/server/details/message_handler.hpp"

#include <zmq.hpp>

#include <string>
#include <experimental/string_view>
#include <memory>

namespace usl::common::communication::server
{
    class server
    {
    public:
        server(zmq::context_t& context);

        void bind(std::experimental::string_view bind_address);

        void run();

        template <typename T>
        void set_message_handler(T message_handler)
        {
            using message_handler_t = details::message_handler_impl<T>;
            m_message_handler = std::make_unique<message_handler_t>(std::move(message_handler));
        }

    private:

        zmq::socket_t m_socket;
        std::unique_ptr<details::base_message_handler> m_message_handler;
    };
}
