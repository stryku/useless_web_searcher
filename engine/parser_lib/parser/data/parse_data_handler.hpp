#pragma once

#include "parser/data/details/content_handler.hpp"

#include <memory>
#include <vector>

namespace usl::parser
{
    namespace data
    {
        class parse_data_handler
        {
        public:
            template<typename T>
            void add_content_handler(T content_handler)
            {
                using handler_t = details::content_handler_impl<T>;
                auto handler = std::make_unique<handler_t>(std::move(content_handler));
                m_content_handlers.emplace_back(std::move(handler));
            }

            void parse(std::shared_ptr<data::parse_data_and_response> data_and_response);

        private:
            std::vector<std::unique_ptr<details::base_content_handler>> m_content_handlers;
        };
    }
}
