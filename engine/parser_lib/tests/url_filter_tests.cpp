#include "parser/url/urls_filter.hpp"
#include "utils.hpp"

#include <gmock/gmock.h>

namespace usl::tests
{
    auto get_urls_filter()
    {
        return usl::parser::url::urls_filter{};
    }

    TEST(urls_filter, Empty_get_Empty)
    {
        const auto urls = get_urls_collection("");
        auto filter = get_urls_filter();
        const auto result = filter.filter_urls("", "", urls);

        ASSERT_THAT(result.size(), 0u);
    }

    TEST(utls_filter, ValidRoot_get_OnlyWithRootAtBeginning)
    {
        const auto root = std::string{"ROOT/"};
        const auto empty = "";
        const auto root_foo = root + "foo";
        const auto not_root = "not" + root;

        const auto urls = get_urls_collection(empty, root, root_foo, not_root);
        auto filter = get_urls_filter();
        const auto result = filter.filter_urls(root, "", urls);

        ASSERT_THAT(result.size(), 2u);

        ASSERT_THAT(result.find(root) != result.end(), true);
        ASSERT_THAT(result.find(root_foo) != result.end(), true);

        ASSERT_THAT(result.find(empty), result.end());
        ASSERT_THAT(result.find(not_root), result.end());
    }
}
