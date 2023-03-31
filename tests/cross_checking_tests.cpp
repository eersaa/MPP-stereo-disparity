#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "utils.h"

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

TEST(CrossCheckingTests, ShouldReturnPixel1ValueIfDifferenceBelowThreshold)
{
    int pixel1 = 2;
    int pixel2 = 3;
    int threshold = 1;
    ASSERT_THAT(crossCheck(pixel1, pixel2, threshold), Eq(2));
}
