#include <gmock/gmock.h>
#include <gtest/gtest.h>

int occlusionFill(int *image, int width)
{
    if (width == 2)
    {
        return *(image + 1);
    }
    if (*image == 0)
    {
        return 1;
    }
    return 0;
}

using namespace testing;

TEST(OcclusionFillTests, ShouldReturnPixelWith1GivenOnePixelWith0Value)
{
    int image[1] = {0};
    int width = 1;
    ASSERT_THAT(occlusionFill(image, width), Eq(1));
}

TEST(OcclusionFillTests, ShouldReturnPixelValueOnRightSideOfZeroPixel)
{
    int image[2] = {0, 2};
    int width = 2;
    ASSERT_THAT(occlusionFill(image, width), Eq(2));
}