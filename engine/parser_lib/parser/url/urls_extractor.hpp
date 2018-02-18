#pragma once

#include "common/string_view.hpp"

#include <vector>

namespace usl::parser::url
{
    class urls_extractor
    {
    public:
        std::vector<string_view> extract(string_view content) const;

    private:
        string_view::size_type find_body(string_view content) const;
    };
}
