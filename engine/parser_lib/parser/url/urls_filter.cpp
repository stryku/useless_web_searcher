#include "parser/url/urls_filter.hpp"

#include <algorithm>

namespace usl::parser::url
{
    urls_filter::urls_filter(const usl::parser::url::urls_filter::filter_t &filter)
        : m_filter{ filter }
    {}

    urls_collection_t urls_filter::filter_urls(const std::string& root_url, const urls_collection_t &urls)
    {
        const auto pred = [this, &root_url](const auto& url)
        {
            if(is_url_to_id(url))
            {
                return false;
            }

            return url.find(root_url) == 0u;
        };

        urls_collection_t filtered_urls;

        std::copy_if(std::cbegin(urls), std::cend(urls),
                     std::inserter(filtered_urls, filtered_urls.end()),
                     pred);

        return filtered_urls;
    }

    bool urls_filter::is_url_to_id(const std::string& url) const
    {
        return url.find('#') != std::string::npos;
    }

    bool urls_filter::is_relative(const std::string& url) const
    {
        return url.front() == '/' &&
               url.find("//www.") == string_view::npos &&
               url.find("http://") == string_view::npos;
    }
}
