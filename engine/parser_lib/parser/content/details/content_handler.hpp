#pragma once

#include <string>

namespace usl::parser::content::details
{
    class base_content_handler
    {
    public:
        virtual void handle(const std::string& content) = 0;
    };

    template <typename T>
    class content_handler_impl : public base_content_handler
    {
    public:
        content_handler_impl(T content_handler)
            : m_content_handler{ std::move(content_handler) }
        {}

        void handle(const std::string& content) override
        {
            m_content_handler.handle(content);
        }

    private:
        T m_content_handler;
    };
}
