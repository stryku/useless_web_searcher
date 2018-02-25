#pragma once

#include <memory>
#include <string>

namespace usl::parser::data
{
    class parse_data_and_response;

    namespace details
    {
        class base_content_handler
        {
        public:
            virtual void handle(std::shared_ptr<data::parse_data_and_response>) = 0;
        };

        template<typename T>
        class content_handler_impl : public base_content_handler
        {
        public:
            content_handler_impl(T content_handler)
                    : m_content_handler{std::move(content_handler)}
            {}

            void handle(std::shared_ptr<data::parse_data_and_response> parse_data) override
            {
                m_content_handler.handle(parse_data);
            }

        private:
            T m_content_handler;
        };
    }
}
