#include "parser/url/urls_handler.hpp"

#include "parser/url/urls_extractor.hpp"
#include "parser/url/urls_filter.hpp"

namespace usl::parser::url
{
    urls_handler::urls_handler(const std::string &db_address)
        : m_db_requester{ db_address }
    {}

    void urls_handler::handle(const std::string& url, const std::string& content, size_t id)
    {
        const auto urls = urls_extractor{}.extract(url, content);

        LOG(INFO) << "extracted urls: " << urls.size();
        for(const auto url : urls)
        {
            LOG(INFO) << url;
        }

        const auto filtered_urls = urls_filter{{}}.filter_urls(urls);

        LOG(INFO) << "filtered urls: " << filtered_urls.size();
        for(const auto url : filtered_urls)
        {
            LOG(INFO) << url;
            m_db_requester.insert(std::string{ url.data(), url.size() });
        }
    }
}
