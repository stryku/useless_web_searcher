#pragma once

#include "common/string_view.hpp"

#include <unordered_set>

namespace usl::parser::url
{
    using urls_collection_t = std::unordered_set<string_view>;
}
