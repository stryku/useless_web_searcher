#include "parser/url/urls_filter.hpp"

#include <algorithm>

namespace usl::parser::url
{
    urls_collection_t urls_filter::filter_urls(const std::string& root_url, const std::string& current_url, const urls_collection_t &urls)
    {
        const auto pred = [this, &root_url, &current_url](const auto& url)
        {
            if(is_url_to_self_id(url, current_url))
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

    bool urls_filter::is_url_to_self_id(const std::string& current_url, const std::string& url) const
    {
        return url.find('#') == current_url.size();
    }

    bool urls_filter::is_relative(const std::string& url) const
    {
        return url.front() == '/' &&
               url.find("//www.") == string_view::npos &&
               url.find("http://") == string_view::npos;
    }
}
