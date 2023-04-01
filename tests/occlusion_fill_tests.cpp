#include <gmock/gmock.h>
#include <gtest/gtest.h>

int occlusionFill(int pixel_index, int *image, int width)
{
    int fillPixelValue = 0;
    int leftRange = 0 - pixel_index;
    int rightRange = width - pixel_index;

    for (int i = leftRange; i < rightRange; i++)
    {
        if (*(image + pixel_index + i) != 0)
        {
            fillPixelValue = *(image + pixel_index + i);
            break;
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
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width), Eq(1));
}

class OcclusionFillTwoPixelTests : public ::testing::Test
{
public:
    int width = 2;
};

TEST_F(OcclusionFillTwoPixelTests, ShouldReturnPixelValueOnRightSideOfZeroPixel)
{
    int image[2] = {0, 2};
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width), Eq(2));
}

TEST_F(OcclusionFillTwoPixelTests, ShouldReturnPixelValueOnLeftSideOfZeroPixel)
{
    int image[2] = {2, 0};
    int pixelIndex = 1;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width), Eq(2));
}

class OcclusionFillThreePixelTests : public ::testing::Test
{
public:
    int width = 3;
};

TEST_F(OcclusionFillThreePixelTests, ShouldReturnPixelValueOnRightmostSideOfZeroPixel)
{
    int image[3] = {0, 0, 3};
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width), Eq(3));
}

TEST_F(OcclusionFillThreePixelTests, ShouldReturnPixelValueOnLeftmostSideOfZeroPixel)
{
    int image[3] = {3, 0, 0};
    int pixelIndex = 2;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width), Eq(3));
}

TEST_F(OcclusionFillThreePixelTests, ShouldReturnPixelValueOnRightWhenMiddleIndexIsZero)
{
    int image[3] = {0, 0, 3};
    int pixelIndex = 1;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width), Eq(3));
}

TEST_F(OcclusionFillThreePixelTests, ShouldReturnPixelValueOnLeftWhenMiddleIndexIsZero)
{
    int image[3] = {3, 0, 0};
    int pixelIndex = 1;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width), Eq(3));
}

TEST(OcclusionFillTwoVerticalPixelsTests, ShouldReturnPixelValueOnBottomSideOfZeroPixel)
{
    int image[2] = {0, 2};
    int width = 1;
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(2));
}
