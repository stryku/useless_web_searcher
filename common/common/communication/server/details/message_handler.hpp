#pragma once

#include <zmq.hpp>

namespace usl::common::communication::server::details
{
    class base_message_handler
    {
    public:
        virtual zmq::message_t handle(const zmq::message_t& message) = 0;
    };

    template <typename T>
    class message_handler_impl : public base_message_handler
    {
    public:
        message_handler_impl(T message_handler)
                : m_message_handler{ std::move(message_handler) }
        {}

        zmq::message_t handle(const zmq::message_t& message) override
        {
            return m_message_handler.handle(message);
        }

    private:
        T m_message_handler;
    };
}
