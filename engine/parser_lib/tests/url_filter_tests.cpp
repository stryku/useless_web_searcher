#include "parser/url/urls_filter.hpp"

#include <gmock/gmock.h>

TEST(url_filter, Empty_get_Empty)
{
    usl::parser::url::urls_collection_t urls = { { "" } };

    usl::parser::url::urls_filter filter;
    const auto result = filter.filter_urls("", "", urls);

    ASSERT_THAT(result.size(), 0u);
}
