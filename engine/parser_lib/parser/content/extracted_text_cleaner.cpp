#include "parser/content/extracted_text_cleaner.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/replace_if.hpp>

namespace usl::parser::content
{
    std::string extracted_text_cleaner::clean(std::string text) const
    {
        const auto k_patterns = { '\r', '\t', '\n' };
        boost::replace_if(text, boost::is_any_of(k_patterns), ' ');

        const auto pred = [](char l, char r)
        {
            return std::isspace(l) && std::isspace(r) && l == r;
        };

        auto end = std::unique(text.begin(), text.end(), pred);
        return std::string{ text.begin(), end };
    }
}
