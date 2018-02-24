#include "parser/content/extracted_text_cleaner.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/replace_if.hpp>
#include <boost/regex.hpp>
#include <easylogging/easylogging++.h>

namespace usl::parser::content
{
    std::string extracted_text_cleaner::clean(std::string text) const
    {
        const auto k_patterns = { '\r', '\t', '\n', '.', ':', '/', '\\' };
        boost::replace_if(text, boost::is_any_of(k_patterns), ' ');

        const auto pred = [](char l, char r)
        {
            return std::isspace(l) && std::isspace(r) && l == r;
        };

        auto end = std::unique(text.begin(), text.end(), pred);
        const auto result = std::string{ text.begin(), end };

        end = remove_special_html_characters(text.begin(), end);

        LOG(INFO) << std::string{ text.begin(), end };

        return std::string{ text.begin(), end };
    }

    std::string::iterator extracted_text_cleaner::remove_special_html_characters(std::string::iterator begin, std::string::iterator end) const
    {
        auto dest = begin;
        auto src = begin;

        std::string tmp;

        while(src != end)
        {
            if(*src == '&')
            {
                while(*src++ != ';')
                {
                    if(src == end)
                    {
                        return dest;
                    }
                }
            }
            else
            {
                tmp += *src;
                *dest++ = *src++;
            }
        }

        return dest;
    }
}
