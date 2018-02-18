#pragma once

#include "common/string_view.hpp"
#include "parser/url/urls_collection.hpp"

#include <boost/optional.hpp>

#include <vector>
#include <string>

namespace usl::parser::url
{
    class urls_extractor
    {
    public:
        urls_collection_t extract(const std::string& url, const std::string& content) const;

    private:
        using pos_t = string_view::size_type;

        struct string_view_and_end_pos
        {
            std::string view;
            pos_t end_pos;
        };

        pos_t find_body(string_view content) const;
        boost::optional<string_view_and_end_pos> find_next_url(string_view content, pos_t pos) const;
    };
}
