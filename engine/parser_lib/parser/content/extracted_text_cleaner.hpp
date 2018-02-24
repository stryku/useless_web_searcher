#pragma once

#include <string>

namespace usl::parser::content
{
    class extracted_text_cleaner
    {
    public:
        std::string clean(std::string text) const;
    };
}
