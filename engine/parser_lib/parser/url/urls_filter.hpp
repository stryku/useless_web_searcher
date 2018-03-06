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

        urls_collection_t filter_urls(const std::string& root_url, const std::string& current_url, const urls_collection_t& urls);

    private:
        // Checks if url is an url to id within the same page
        bool is_url_to_self_id(const std::string& current_url, const std::string& url) const;
        bool is_relative(const std::string& url) const;
    };
}
