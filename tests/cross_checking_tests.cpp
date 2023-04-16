#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "utils.h"

using namespace testing;

TEST(CrossCheckPixelTests, ShouldReturnZeroOutputPixelGivenTwoZeroInputPixels)
{
    unsigned char pixel1 = 0;
    unsigned char pixel2 = 0;
    int threshold = 0;
    ASSERT_THAT(crossCheck(pixel1, pixel2, threshold), Eq(0));
}

TEST(CrossCheckPixelTests, ShouldReturnOneGivenTwoPixelsWithValueOfOne)
{
    unsigned char pixel1 = 1;
    unsigned char pixel2 = 1;
    int threshold = 0;
    ASSERT_THAT(crossCheck(pixel1, pixel2, threshold), Eq(1));
}

TEST(CrossCheckPixelTests, ShouldReturnZeroIfPixelDifferenceOverThreshold)
{
    unsigned char pixel1 = 1;
    unsigned char pixel2 = 2;
    int threshold = 0;
    ASSERT_THAT(crossCheck(pixel1, pixel2, threshold), Eq(0));
}

TEST(CrossCheckPixelTests, ShouldReturnPixel1ValueIfDifferenceBelowThreshold)
{
    unsigned char pixel1 = 2;
    unsigned char pixel2 = 3;
    int threshold = 1;
    ASSERT_THAT(crossCheck(pixel1, pixel2, threshold), Eq(2));
}

TEST(CrossCheckTwoImagesTests, ShouldReplacePixelWithZeroIfPixelDifferenceOverThreshold)
{
    unsigned char image1[4] = {0, 1, 2, 3};
    unsigned char image2[4] = {3, 2, 1, 0};
    int threshold = 1;
    unsigned char outputImage[4];
    int imageSize = 4;
    crossCheckTwoImages(image1, image2, threshold, outputImage, imageSize);
    ASSERT_THAT(outputImage, AllOf(ElementsAre(0, 1, 2, 0)));
}
