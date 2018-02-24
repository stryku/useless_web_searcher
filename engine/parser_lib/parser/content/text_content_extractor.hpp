#pragma once

#include <string>

namespace usl::parser::content
{
    class text_content_extractor
    {
    public:
        std::string extract(const std::string& site_content) const;

    private:
        using pos_t = std::string::size_type;
        using pos_bounds_t = std::pair<pos_t, pos_t>;

        pos_bounds_t find_body_pos(const std::string& site_content) const;
        std::string extract_text(const pos_bounds_t& body_bounds) const;
        pos_bounds_t find_next_text(const std::string& content, pos_t from) const;
    };
}