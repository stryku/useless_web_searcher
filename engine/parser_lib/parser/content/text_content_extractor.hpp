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

        pos_bounds_t find_body_bounds() const;
        std::string extract_text(pos_bounds_t body_bounds) const;
        pos_bounds_t get_text_till_next_tag(pos_t from) const;
        pos_bounds_t get_next_tag(pos_t tag_start) const;

        bool is_script_tag(pos_bounds_t tag) const;

        // Returns pos after </script>
        pos_t skip_script_tag(pos_bounds_t begin_script_tag_bounds) const;

        // Returns pos after tag >
        pos_t skip_next_tag(pos_t current_pos) const;

    private:
        const std::string& m_site_content;
    };
}