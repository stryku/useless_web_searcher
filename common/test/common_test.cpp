#include <gmock/gmock.h>
#include "common.hpp"

namespace test
{


TEST(SuiteName, PassingTest)
{
//    FAIL();
    // given:


    ASSERT_THAT(common_tmp(), 0);
    // when:

    //expected:

}
} // namespace test
