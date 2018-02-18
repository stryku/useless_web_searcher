#pragma once

#include "parser/content/details/content_handler.hpp"

#include <memory>
#include <vector>

namespace usl::parser::content
{
    class content_parser
    {
    public:


        template <typename T>
        void add_content_handler(T content_handler)
        {
            using handler_t = details::content_handler_impl<T>;
            auto handler = std::make_unique<handler_t>(std::move(content_handler));
            m_content_handlers.emplace_back(std::move(handler));
        }

    private:
        std::vector<std::unique_ptr<details::base_content_handler>> m_content_handlers;
    };
}
