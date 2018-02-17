#pragma once

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

        template <typename T>
        void set_message_handler(T message_handler)
        {
            using message_handler_t = message_handler_impl<T>;
            m_message_handler = std::make_unique<message_handler_t>(std::move(message_handler));
        }

    private:
        class base_message_handler
        {
        public:
            virtual void handle(const std::string& message) = 0;
        };

        template <typename T>
        class message_handler_impl : public base_message_handler
        {
        public:
            message_handler_impl(T message_handler)
                : m_message_handler{ std::move(message_handler) }
            {}

            void handle(const std::string& message) override
            {
                m_message_handler.handle(message);
            }

        private:
            T m_message_handler;
        };

        zmq::socket_t m_socket;
        std::unique_ptr<base_message_handler> m_message_handler;
    };
}
