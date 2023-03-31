#include <gmock/gmock.h>
#include <gtest/gtest.h>

int crossCheck(int pixel1, int pixel2)
{
    return 0;
}

using namespace testing;

TEST(CrossCheckingTests, ShouldReturnZeroOutputPixelGivenTwoZeroInputPixels)
{
    int pixel1 = 0;
    int pixel2 = 0;
    ASSERT_THAT(crossCheck(pixel1, pixel2), Eq(0));
}