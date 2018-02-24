#include "parser/url/urls_handler.hpp"

#include "parser/url/urls_extractor.hpp"
#include "parser/url/urls_filter.hpp"
#include "parser/url/url_info.hpp"

namespace usl::parser::url
{
    urls_handler::urls_handler(const std::string &db_address)
        : m_db_requester{ db_address }
    {}

    void urls_handler::handle(const std::string& current_url, const std::string& content, size_t id)
    {
        const auto extracted_urls = urls_extractor{}.extract(current_url, content);

        const auto root_url = info::site_root(current_url);
        const auto filtered_urls = urls_filter{{}}.filter_urls(root_url, current_url, extracted_urls);

        for(const auto url : filtered_urls)
        {
            m_db_requester.insert(std::string{ url.data(), url.size() });
        }
    }
}
