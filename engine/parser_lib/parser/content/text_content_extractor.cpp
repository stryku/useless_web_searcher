#include "text_content_extractor.hpp"

namespace usl::parser::content
{
    text_content_extractor::text_content_extractor(const std::string &site_content)
        : m_site_content{ site_content }
    {}

    std::string text_content_extractor::extract() const
    {

        return std::__cxx11::string();
    }

    text_content_extractor::pos_bounds_t text_content_extractor::find_body_pos() const
    {
        const auto begin = m_site_content.find("<body");
        const auto end = m_site_content.rfind("</body", begin);
        return { begin, end };
    }

    std::string text_content_extractor::extract_text(const text_content_extractor::pos_bounds_t& body_bounds) const
    {
        auto tag_begin = body_bounds.first;
        auto next_tag = get_next_tag(tag_begin);

        if(is_script_tag(next_tag))
        {

        }

    }

    text_content_extractor::pos_bounds_t text_content_extractor::find_next_text(text_content_extractor::pos_t from) const
    {
        const auto next_tag_begin = m_site_content.find('<', from);
        return { from, next_tag_begin };
    }

    pos_bounds_t text_content_extractor::get_next_tag(text_content_extractor::pos_t tag_start) const
    {
        const auto tag_end = m_site_content.find('>', tag_start);
        return pos_bounds_t{ tag_start, tag_end };
    }

    bool text_content_extractor::is_script_tag(pos_bounds_t tag) const
    {
        const auto tag_view_begin = std::next(m_site_content.c_str(), tag.first);
        const auto tag_view = string_view{ tag_view_begin };
        return tag_view.find("<script") == pos_t{ 0u };
    }
}
