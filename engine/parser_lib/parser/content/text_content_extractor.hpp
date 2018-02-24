#pragma once

#include <string>

namespace usl::parser::content
{
    class text_content_extractor
    {
    public:
        std::string extract(const std::string& site_content) const;
    };
}