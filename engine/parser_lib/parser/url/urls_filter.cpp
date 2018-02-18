#include "parser/url/urls_filter.hpp"

#include <algorithm>

namespace usl::parser::url
{
    urls_filter::urls_filter(const usl::parser::url::urls_filter::filter_t &filter)
        : m_filter{ filter }
    {}

    urls_collection_t urls_filter::filter_urls(const urls_collection_t &urls)
    {
        const auto pred = [this](auto url)
        {
            if(is_url_to_id(url))
            {
                return false;
            }

            if(!is_relative(url))
            {
                if(m_filter.empty())
                {
                    return false;
                }

                for(const auto& url_filter : m_filter)
                {
                    if(url.find(url_filter.c_str()) != 0u)
                    {
                        return false;
                    }
                }
            }

            return true;
        };

        urls_collection_t filtered_urls;

        std::copy_if(std::cbegin(urls), std::cend(urls),
                     std::inserter(filtered_urls, filtered_urls.end()),
                     pred);

        return filtered_urls;
    }

    bool urls_filter::is_url_to_id(string_view url) const
    {
        return url.front() == '#';
    }

    bool urls_filter::is_relative(string_view url) const
    {
        return url.front() == '/' &&
               url.find("//www.") == string_view::npos &&
               url.find("http://") == string_view::npos;
    }
}
