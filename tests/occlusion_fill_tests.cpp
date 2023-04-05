#include <gmock/gmock.h>
#include <gtest/gtest.h>

int occlusionFill(int pixel_index, int *image, int width, int height)
{
    int fillPixelValue = 0;
    if (width == 2 || height == 2)
    {
        if (pixel_index == 0)
        {
            fillPixelValue = *(image + 1);
        }
        else
        {
            fillPixelValue = *(image);
        }
    }
    if (fillPixelValue == 0)
    {
        fillPixelValue = 1;
    }
    return fillPixelValue;
}

using namespace testing;

TEST(OcclusionFillOnePixelTest, ShouldReturnPixelWith1GivenPixelWith0Value)
{
    int image[1] = {0};
    int width = 1;
    int height = 1;
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(1));
}

class OcclusionFillTwoPixelTests : public ::testing::Test
{
public:
    int width = 2;
    int height = 1;
};

TEST_F(OcclusionFillTwoPixelTests, ShouldReturnPixelValueOnRightSideOfZeroPixel)
{
    int image[2] = {0, 2};
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(2));
}

TEST_F(OcclusionFillTwoPixelTests, ShouldReturnPixelValueOnLeftSideOfZeroPixel)
{
    int image[2] = {2, 0};
    int pixelIndex = 1;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(2));
}

TEST(OcclusionFillTwoVerticalPixelTests, ShouldReturnPixelValueOnTopOfZeroPixel)
{
    int image[2] = {2, 0};
    int width = 1;
    int height = 2;
    int pixelIndex = 1;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(2));
}