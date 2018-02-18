#include "parser/url/urls_extractor.hpp"

namespace usl::parser::url
{
    std::vector<string_view> urls_extractor::extract(string_view content) const
    {
        std::vector<string_view> urls;

        auto pos = find_body(content);

        return urls;
    }

    string_view::size_type urls_extractor::find_body(string_view content) const
    {
        return content.find("<body");
    }
}
