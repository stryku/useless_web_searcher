#include "parser/url/urls_handler.hpp"

#include "parser/url/urls_extractor.hpp"

namespace usl::parser::url
{
    void urls_handler::handle(const std::string &content)
    {
        const auto urls = urls_extractor{}.extract(content);

        LOG(INFO) << "extracted urls: " << urls.size();
        for(const auto url : urls)
        {
            LOG(INFO) << url;
        }
    }
}
