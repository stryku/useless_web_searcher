#pragma once

#include "common/string_view.hpp"

#include <string>

namespace usl::parser::content
{
    class text_content_extractor
    {
    public:
        text_content_extractor(const std::string& site_content);

        std::string extract() const;

    private:
        using pos_t = std::string::size_type;
        using pos_bounds_t = std::pair<pos_t, pos_t>;

        pos_bounds_t find_body_pos() const;
        std::string extract_text(const pos_bounds_t& body_bounds) const;
        pos_bounds_t find_next_text(pos_t from) const;
        pos_bounds_t get_next_tag(pos_t tag_start) const;

        bool is_script_tag(pos_bounds_t tag) const;
        pos_t skip_script_tag()

    private:
        const std::string& m_site_content;
    };
}