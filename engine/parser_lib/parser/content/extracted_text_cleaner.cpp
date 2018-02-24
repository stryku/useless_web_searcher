#include "parser/content/extracted_text_cleaner.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/replace_if.hpp>

namespace usl::parser::content
{
    std::string extracted_text_cleaner::clean(const std::string text) const
    {
        const auto k_patterns = { "\r\n\t\n" };
        auto replaced = boost::replace_if(text, boost::is_any_of(k_patterns), ' ');

        const auto pred = [](char l, char r)
        {
            return std::isspace(l) && std::isspace(r) && l == r;
        };

        auto end = std::unique(replaced.begin(), replaced.end(), pred);
        return std::string{ replaced.begin(), end };
    }
}
