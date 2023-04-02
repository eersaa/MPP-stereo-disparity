#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "occlusion_fill.h"


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

class OcclusionFillThreePixelTests : public ::testing::Test
{
public:
    int width = 3;
    int height = 1;
};

TEST_F(OcclusionFillThreePixelTests, ShouldReturnPixelValueOnRightmostSideOfZeroPixel)
{
    int image[3] = {0, 0, 3};
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}

TEST_F(OcclusionFillThreePixelTests, ShouldReturnPixelValueOnLeftmostSideOfZeroPixel)
{
    int image[3] = {3, 0, 0};
    int pixelIndex = 2;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}

TEST_F(OcclusionFillThreePixelTests, ShouldReturnPixelValueOnRightWhenMiddleIndexIsZero)
{
    int image[3] = {0, 0, 3};
    int pixelIndex = 1;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}

TEST_F(OcclusionFillThreePixelTests, ShouldReturnPixelValueOnLeftWhenMiddleIndexIsZero)
{
    int image[3] = {3, 0, 0};
    int pixelIndex = 1;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}


class OcclusionFillTwoVerticalPixelsTests : public ::testing::Test
{
public:
    int width = 1;
    int height = 2;
};

TEST_F(OcclusionFillTwoVerticalPixelsTests, ShouldReturnPixelValueBelowZeroPixel)
{
    int image[2] = {0, 2};
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(2));
}

TEST_F(OcclusionFillTwoVerticalPixelsTests, ShouldReturnPixelValueAboveZeroPixel)
{
    int image[2] = {2, 0};
    int pixelIndex = 1;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(2));
}

class OcclusionFillThreeVerticalPixelsTests : public ::testing::Test
{
public:
    int width = 1;
    int height = 3;
};

TEST_F(OcclusionFillThreeVerticalPixelsTests, ShouldReturnPixelValueBelowZeroPixel)
{
    int image[3] = {0, 0, 3};
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}

TEST_F(OcclusionFillThreeVerticalPixelsTests, ShouldReturnPixelValueAboveZeroPixel)
{
    int image[3] = {3, 0, 0};
    int pixelIndex = 2;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}

TEST_F(OcclusionFillThreeVerticalPixelsTests, ShouldReturnPixelValueBelowWhenMiddleIndexIsZero)
{
    int image[3] = {0, 0, 3};
    int pixelIndex = 1;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}

TEST_F(OcclusionFillThreeVerticalPixelsTests, ShouldReturnPixelValueAboveWhenMiddleIndexIsZero)
{
    int image[3] = {3, 0, 0};
    int pixelIndex = 1;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}
