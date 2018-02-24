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

    std::string text_content_extractor::extract_text(const pos_bounds_t& body_bounds) const
    {
        std::string extracted_text;
        extracted_text.reserve(body_bounds.second - body_bounds.first);

        auto current_pos = body_bounds.first;

        while(current_pos < body_bounds.second)
        {
            current_pos = skip_next_tag(current_pos);
            const auto text_bounds = get_text_till_next_tag(current_pos);

            const auto text_begin = std::next(m_site_content, text_bounds.first);
            const auto text_end = std::next(m_site_content, text_bounds.second);
            extracted_text.append(text_begin, text_end);

            current_pos = text_bounds.second;
        }

        return extracted_text;
    }

    text_content_extractor::pos_bounds_t text_content_extractor::get_text_till_next_tag(pos_t from) const
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

    text_content_extractor::pos_t text_content_extractor::skip_script_tag(pos_bounds_t begin_script_tag_bounds) const
    {
        const auto k_end_script_tag = "</script>";
        const auto script_code_begin = begin_script_tag_bounds.second;
        const auto end_script_tag_begin = m_site_content.find(k_end_script_tag, script_code_begin);
        const auto end_script_tag_end = end_script_tag_begin + std::size(k_end_script_tag);

        return end_script_tag_end;
    }

    text_content_extractor::pos_t text_content_extractor::skip_next_tag(pos_t current_pos) const
    {
        const auto next_tag = get_next_tag(current_pos);

        if(is_script_tag(next_tag))
        {
            return skip_script_tag(next_tag);
        }
        else
        {
            return next_tag.second;
        }
    }
    text_content_extractor::pos_bounds_t text_content_extractor::get_text_till_next_tag(pos_t current_pos) const
    {
        con
    }
}
