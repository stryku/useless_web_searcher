#include "text_content_extractor.hpp"

namespace usl::parser::content
{
    std::string text_content_extractor::extract(const std::string &site_content) const
    {

        return std::__cxx11::string();
    }

    text_content_extractor::body_bounds_t text_content_extractor::find_body_pos(const std::string& site_content) const
    {
        const auto begin = site_content.find("<body");
        const auto end = site_content.find("</body", begin);
        return { begin, end };
    }
}
