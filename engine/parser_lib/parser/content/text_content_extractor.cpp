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

    }

    text_content_extractor::pos_bounds_t text_content_extractor::find_next_text(text_content_extractor::pos_t from) const
    {
        const auto next_tag_begin = m_site_content.find('<', from);
        return { from, next_tag_begin };
    }

    string_view text_content_extractor::get_next_tag(text_content_extractor::pos_t tag_start) const
    {
        const auto tag_end = m_site_content.find('>', tag_start);
        const auto tag_size = tag_end - tag_start;
        return string_view{ m_site_content.c_str(), tag_size };
    }
}
