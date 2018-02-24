#include "parser/url/urls_handler.hpp"

#include "parser/data/parse_data_and_response.hpp"
#include "parser/url/urls_extractor.hpp"
#include "parser/url/urls_filter.hpp"
#include "parser/url/url_info.hpp"

namespace usl::parser::url
{
    urls_handler::urls_handler(const std::string &db_address)
        : m_db_requester{ db_address }
    {}

    void urls_handler::handle(std::shared_ptr<data::parse_data_and_response> parse_data)
    {
        LOG(INFO) << "urls_handler handling: " << parse_data->data().id;

        const auto& data = parse_data->data();
        const auto extracted_urls = urls_extractor{}.extract(data.url, data.data);

        const auto root_url = info::site_root(data.url);
        const auto filtered_urls = urls_filter{{}}.filter_urls(root_url, data.url, extracted_urls);

        LOG(INFO) << "urls_handler filtered urls: " << filtered_urls.size();

        for(const auto url : filtered_urls)
        {
            m_db_requester.insert(std::string{ url.data(), url.size() });
        }
    }
}
