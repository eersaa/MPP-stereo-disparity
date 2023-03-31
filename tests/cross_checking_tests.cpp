#include <gmock/gmock.h>
#include <gtest/gtest.h>

int crossCheck(int pixel1, int pixel2, int threshold)
{
    if (abs(pixel1 - pixel2) > threshold)
    {
        return 0;
    }
    
    return pixel1;
}

using namespace testing;

TEST(CrossCheckingTests, ShouldReturnZeroOutputPixelGivenTwoZeroInputPixels)
{
    int pixel1 = 0;
    int pixel2 = 0;
    int threshold = 0;
    ASSERT_THAT(crossCheck(pixel1, pixel2, threshold), Eq(0));
}

TEST(CrossCheckingTests, ShouldReturnOneGivenTwoPixelsWithValueOfOne)
{
    int pixel1 = 1;
    int pixel2 = 1;
    int threshold = 0;
    ASSERT_THAT(crossCheck(pixel1, pixel2, threshold), Eq(1));
}

TEST(CrossCheckingTests, ShouldReturnZeroIfPixelDifferenceOverThreshold)
{
    int pixel1 = 1;
    int pixel2 = 2;
    int threshold = 0;
    ASSERT_THAT(crossCheck(pixel1, pixel2, threshold), Eq(0));
}