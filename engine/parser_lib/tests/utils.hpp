#pragma once

#include "parser/url/urls_collection.hpp"

namespace usl::tests
{
    template <typename... Args>
    auto get_urls_collection(Args&&... args)
    {
        return parser::url::urls_collection_t{ std::string(args)... };
    }
}
