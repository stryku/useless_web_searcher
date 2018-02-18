#pragma once

#include "common/string_view.hpp"
#include "parser/url/urls_collection.hpp"

#include <string>
#include <unordered_set>

namespace usl::parser::url
{
    class urls_filter
    {
    public:
        using filter_t = std::unordered_set<std::string>;

        explicit urls_filter(const filter_t& filter);

        urls_collection_t filter_urls(const std::string& root_url, const urls_collection_t& urls);

    private:
        bool is_url_to_id(const std::string& url) const;
        bool is_relative(const std::string& url) const;

        const filter_t m_filter;
    };
}
