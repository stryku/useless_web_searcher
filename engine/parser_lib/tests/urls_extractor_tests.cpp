#include "parser/url/urls_extractor.hpp"
#include "utils.hpp"

#include <gmock/gmock.h>

namespace usl::tests
{
    auto get_urls_extractor()
    {
        return usl::parser::url::urls_extractor{};
    }

    TEST(urls_extractor, Empty_get_Empty)
    {
        const auto test_source = "";
        auto extractor = get_urls_extractor();
        const auto result = extractor.extract("", test_source);

        ASSERT_THAT(result.size(), 0u);
    }

    TEST(urls_extractor, UrlInHeader_Ignore)
    {
        const auto test_source = "<head><a href=\"dummy.com\">dummy</a></head><body></body>";
        auto extractor = get_urls_extractor();
        const auto result = extractor.extract("", test_source);

        ASSERT_THAT(result.size(), 0u);
    }
}
