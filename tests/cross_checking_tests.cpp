#include <gmock/gmock.h>
#include <gtest/gtest.h>

int crossCheck()
{
    return 0;
}

using namespace testing;

TEST(CrossCheckingTests, ShouldReturnZeroOutputPixelGivenTwoZeroInputPixels)
{
    ASSERT_THAT(crossCheck(), Eq(0));
}