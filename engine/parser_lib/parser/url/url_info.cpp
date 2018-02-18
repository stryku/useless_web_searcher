#include "parser/url/url_info.hpp"

namespace usl::parser::url::info
{
    bool is_absolute(const std::string& url)
    {
        return url.find("//www.") != std::string::npos ||
               url.find("http://") != std::string::npos;
    }

    std::string site_root(const std::string& url)
    {
        const auto backslashes = "//";
        auto pos = url.find("//");

        if(pos == std::string::npos)
        {
            return {};
        }

        pos = url.find('/', pos + std::size(backslashes));

        return url.substr(0, pos);
    }
}
