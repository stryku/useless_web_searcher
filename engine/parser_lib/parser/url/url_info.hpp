#pragma once

#include <string>

namespace usl::parser::url::info
{
    bool is_absolute(const std::string& url);
    std::string site_root(const std::string& url);
}
