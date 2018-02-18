#include "parser/url/urls_extractor.hpp"

#include "parser/url/url_info.hpp"

namespace usl::parser::url
{
    urls_collection_t urls_extractor::extract(const std::string& source_url, const std::string& content) const
    {
        urls_collection_t urls;

        auto pos = find_body(content);
        auto found_url = find_next_url(content, pos);

        while(found_url)
        {
            auto absolute_url = make_absolute_url(source_url, found_url->url);
            urls.emplace(std::move(absolute_url));
            found_url = find_next_url(content, found_url->end_pos);
        }

        return urls;
    }

    urls_extractor::pos_t urls_extractor::find_body(string_view content) const
    {
        return content.find("<body");
    }

    boost::optional<urls_extractor::url_and_end_pos> urls_extractor::find_next_url(const std::string& content, pos_t pos) const
    {
        const auto href_pattern = std::string{ "href=\"" };
        const auto href_pos = content.find(href_pattern, pos);

        if(href_pos == string_view::npos)
        {
            return boost::none;
        }

        const auto url_start = href_pos + href_pattern.size();
        const auto url_end = content.find("\"", url_start);
        const auto url_size = url_end - url_start;

        const auto url = std::string{ content.c_str() + url_start, url_size};

        return url_and_end_pos{ url, url_end };
    }

    std::string urls_extractor::make_absolute_url(const std::string &source_url, const std::string &url) const
    {
        if(info::is_absolute(url))
        {
            return url;
        }

        const auto root = info::site_root(source_url);

        return root + url;
    }
}
