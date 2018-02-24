#include "text_content_extractor.hpp"

namespace usl::parser::content
{
    std::string text_content_extractor::extract(const std::string &site_content) const
    {

        return std::__cxx11::string();
    }

    text_content_extractor::pos_bounds_t text_content_extractor::find_body_pos(const std::string& site_content) const
    {
        const auto begin = site_content.find("<body");
        const auto end = site_content.find("</body", begin);
        return { begin, end };
    }

    std::string text_content_extractor::extract_text(const text_content_extractor::pos_bounds_t& body_bounds) const
    {
    }

    text_content_extractor::pos_bounds_t text_content_extractor::find_next_text(const std::string &content,
                                                                                text_content_extractor::pos_t from) const
    {
        const auto next_tag_begin = content.find('<', from);
        return { from, next_tag_begin };
    }
}
