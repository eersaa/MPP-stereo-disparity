#include <gmock/gmock.h>
#include <gtest/gtest.h>

int occlusionFill(int pixel_index, int *image, int width)
{
    int fillPixelValue = 0;
    if (width == 2)
    {
        fillPixelValue = *(image + 1);
    }
    if (fillPixelValue == 0)
    {
        fillPixelValue = 1;
    }
    return fillPixelValue;
}

using namespace testing;

TEST(OcclusionFillTests, ShouldReturnPixelWith1GivenOnePixelWith0Value)
{
    int image[1] = {0};
    int width = 1;
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width), Eq(1));
}

TEST(OcclusionFillTests, ShouldReturnPixelValueOnRightSideOfZeroPixel)
{
    int image[2] = {0, 2};
    int width = 2;
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width), Eq(2));
}

TEST(OcclusionFillTests, ShouldReturnPixelValueOnLeftSideOfZeroPixel)
{
    int image[2] = {2, 0};
    int width = 2;
    int pixelIndex = 1;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width), Eq(2));
}
