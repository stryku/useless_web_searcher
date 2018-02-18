#include "parser/url/urls_extractor.hpp"

namespace usl::parser::url
{
    urls_collection_t urls_extractor::extract(string_view content) const
    {
        urls_collection_t urls;

        auto pos = find_body(content);
        auto found_url = find_next_url(content, pos);

        while(found_url)
        {
            urls.emplace(found_url->view);
            found_url = find_next_url(content, found_url->end_pos);
        }

        return urls;
    }

    urls_extractor::pos_t urls_extractor::find_body(string_view content) const
    {
        return content.find("<body");
    }

    boost::optional<urls_extractor::string_view_and_end_pos> urls_extractor::find_next_url(string_view content, pos_t pos) const
    {
        const auto href_pattern = string_view{ "href=\"" };
        const auto href_pos = content.find(href_pattern, pos);

        if(href_pos == string_view::npos)
        {
            return boost::none;
        }

        const auto url_start = href_pos + href_pattern.size();
        const auto url_end = content.find("\"", url_start);
        const auto url_size = url_end - url_start;

        const auto url_view = string_view{ std::next(content.cbegin(), url_start), url_size};

        return string_view_and_end_pos{ url_view, url_end };
    }
}
