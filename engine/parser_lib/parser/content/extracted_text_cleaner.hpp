#pragma once

#include <string>

namespace usl::parser::content
{
    class extracted_text_cleaner
    {
    public:
        std::string clean(std::string text) const;

    private:
        std::string::iterator remove_special_html_characters(std::string::iterator begin, std::string::iterator end) const;
    };
}
