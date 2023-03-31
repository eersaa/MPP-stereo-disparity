#include <gmock/gmock.h>
#include <gtest/gtest.h>

int crossCheck(int pixel1, int pixel2)
{
    return pixel1;
}

using namespace testing;

TEST(CrossCheckingTests, ShouldReturnZeroOutputPixelGivenTwoZeroInputPixels)
{
    int pixel1 = 0;
    int pixel2 = 0;
    ASSERT_THAT(crossCheck(pixel1, pixel2), Eq(0));
}

TEST(CrossCheckingTests, ShouldReturnOneGivenTwoPixelsWithValueOfOne)
{
    int pixel1 = 1;
    int pixel2 = 1;
    ASSERT_THAT(crossCheck(pixel1, pixel2), Eq(1));
}

TEST(CrossCheckingTests, ShouldReturnZeroIfDifferenceOverThreshold)
{
    int pixel1 = 1;
    int pixel2 = 2;
    ASSERT_THAT(crossCheck(pixel1, pixel2), Eq(0));
}