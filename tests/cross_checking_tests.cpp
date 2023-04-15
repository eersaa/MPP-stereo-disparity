#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "utils.h"

using namespace testing;

TEST(CrossCheckPixelTests, ShouldReturnZeroOutputPixelGivenTwoZeroInputPixels)
{
    int pixel1 = 0;
    int pixel2 = 0;
    int threshold = 0;
    ASSERT_THAT(crossCheck(pixel1, pixel2, threshold), Eq(0));
}

TEST(CrossCheckPixelTests, ShouldReturnOneGivenTwoPixelsWithValueOfOne)
{
    int pixel1 = 1;
    int pixel2 = 1;
    int threshold = 0;
    ASSERT_THAT(crossCheck(pixel1, pixel2, threshold), Eq(1));
}

TEST(CrossCheckPixelTests, ShouldReturnZeroIfPixelDifferenceOverThreshold)
{
    int pixel1 = 1;
    int pixel2 = 2;
    int threshold = 0;
    ASSERT_THAT(crossCheck(pixel1, pixel2, threshold), Eq(0));
}

TEST(CrossCheckPixelTests, ShouldReturnPixel1ValueIfDifferenceBelowThreshold)
{
    int pixel1 = 2;
    int pixel2 = 3;
    int threshold = 1;
    ASSERT_THAT(crossCheck(pixel1, pixel2, threshold), Eq(2));
}

TEST(CrossCheckTwoImagesTests, ShouldReplacePixelWithZeroIfPixelDifferenceOverThreshold)
{
    int image1[4] = {0, 1, 2, 3};
    int image2[4] = {3, 2, 1, 0};
    int threshold = 1;
    int outputImage[4];
    int imageSize = 4;
    crossCheckTwoImages(image1, image2, threshold, outputImage, imageSize);
    ASSERT_THAT(outputImage, AllOf(ElementsAre(0, 1, 2, 0)));
}
