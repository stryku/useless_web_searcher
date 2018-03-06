#include "parser/url/urls_filter.hpp"

#include <gmock/gmock.h>

template <typename... Args>
auto get_urls_collection(Args&&... args)
{
    return usl::parser::url::urls_collection_t{ std::string(args)... };
}

auto get_urls_filter()
{
    return usl::parser::url::urls_filter{};
}

TEST(url_filter, Empty_get_Empty)
{
    const auto urls = get_urls_collection("");
    auto filter =  get_urls_filter();
    const auto result = filter.filter_urls("", "", urls);

    ASSERT_THAT(result.size(), 0u);
}
