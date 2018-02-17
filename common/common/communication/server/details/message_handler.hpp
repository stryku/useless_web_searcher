#pragma once

namespace usl::common::communication::server::details
{
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
}
