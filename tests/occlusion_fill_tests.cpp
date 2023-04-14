#include "occlusion_fill.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

TEST(EuclideanDistanceTests, ShouldReturnZeroWhenPixelIsOnSamePosition)
{
    int pixel1Index = 0;
    int pixel2xIndex = 0;
    int pixel2yIndex = 0;
    ASSERT_THAT(euclideanDistanceBetweenTwoPixels(pixel1Index, pixel2xIndex, pixel2yIndex), Eq(0));
}

class HorizontalDistanceOneRowTests : public Test
{
public:
    int height = 1;
};

TEST_F(HorizontalDistanceOneRowTests, ShouldReturnZeroWhenPixelIsOnSameColumn)
{
    int pixelIndex = 0;
    int columnIndex = 0;
    ASSERT_THAT(horDistance(pixelIndex, columnIndex, height), Eq(0));
}

TEST_F(HorizontalDistanceOneRowTests, ShouldReturnTwoWhenPixelIsTwoColumnsRight)
{
    int pixelIndex = 2;
    int columnIndex = 0;
    ASSERT_THAT(horDistance(pixelIndex, columnIndex, height), Eq(2));
}

TEST_F(HorizontalDistanceOneRowTests, ShouldReturnTwoWhenPixelIsTwoColumnsLeft)
{
    int pixelIndex = 0;
    int columnIndex = 2;
    ASSERT_THAT(horDistance(pixelIndex, columnIndex, height), Eq(2));
}

TEST(HorizontalDistanceTwoRowTests, ShouldReturnZeroWhenPixelInSameColumnButOnNextRow)
{
    int pixelIndex = 1;
    int columnIndex = 0;
    int height = 2;
    ASSERT_THAT(horDistance(pixelIndex, columnIndex, height), Eq(0));
}

class VerticalDistanceTests : public Test
{
public:
    int width = 1;
};

TEST_F(VerticalDistanceTests, ShouldReturnZeroWhenPixelIsOnSameRow)
{
    int pixelIndex = 0;
    int rowIndex = 0;
    ASSERT_THAT(verDistance(pixelIndex, rowIndex, width), Eq(0));
}

TEST_F(VerticalDistanceTests, ShouldReturnTwoWhenPixelIsTwoRowsBelow)
{
    int pixelIndex = 2;
    int rowIndex = 0;
    ASSERT_THAT(verDistance(pixelIndex, rowIndex, width), Eq(2));
}

TEST_F(VerticalDistanceTests, ShouldReturnTwoWhenPixelIsTwoRowsAbove)
{
    int pixelIndex = 0;
    int rowIndex = 2;
    ASSERT_THAT(verDistance(pixelIndex, rowIndex, width), Eq(2));
}

class VerticalDistance2x2ImageTests : public Test
{
public:
    int width = 2;
};

TEST_F(VerticalDistance2x2ImageTests, ShouldReturnOneWhenPixelIsOnNextRow)
{
    int pixelIndex = 2;
    int rowIndex = 0;
    ASSERT_THAT(verDistance(pixelIndex, rowIndex, width), Eq(1));
}

TEST_F(VerticalDistance2x2ImageTests, ShouldReturnOneWhenPixelIsOnPreviousRow)
{
    int pixelIndex = 0;
    int rowIndex = 1;
    ASSERT_THAT(verDistance(pixelIndex, rowIndex, width), Eq(1));
}


// TEST(OcclusionFillTwoByTwoImageTests, ShouldReturnNearestOnLeft)
// {
//     int image[4] = {4, 0, 3, 2};
//     int pixelIndex = 1;
//     int width = 2;
//     int height = 2;
//     ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(4));
// }


class OcclusionFillTwoByTwoImageFirstRowTests : public Test
{
public:
    int width = 2;
    int height = 2;
};

TEST_F(OcclusionFillTwoByTwoImageFirstRowTests, ShouldReturnPixelValueOnRight)
{
    int image[4] = {0, 4, 0, 0};
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, 2, 2), Eq(4));
}

TEST_F(OcclusionFillTwoByTwoImageFirstRowTests, ShouldReturnPixelValueOnLeft)
{
    int image[4] = {4, 0, 0, 0};
    int pixelIndex = 1;
    ASSERT_THAT(occlusionFill(pixelIndex, image, 2, 2), Eq(4));
}

class OcclusionFillTwoByTwoImageSecondRowTests : public Test
{
public:
    int width = 2;
    int height = 2;
};

TEST_F(OcclusionFillTwoByTwoImageSecondRowTests, ShouldReturnPixelValueOnRight)
{
    int image[4] = {0, 0, 0, 4};
    int pixelIndex = 2;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(4));
}

TEST_F(OcclusionFillTwoByTwoImageSecondRowTests, ShouldReturnPixelValueOnLeft)
{
    int image[4] = {0, 0, 4, 0};
    int pixelIndex = 3;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(4));
}


class OcclusionFillThreeVerticalPixelTests : public Test
{
public:
    int width = 1;
    int height = 3;
};

TEST_F(OcclusionFillThreeVerticalPixelTests, ShouldReturnPixelValueOfBottomPixel)
{
    int image[3] = {0, 0, 3};
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}

TEST_F(OcclusionFillThreeVerticalPixelTests, ShouldReturnPixelValueOfTopPixel)
{
    int image[3] = {3, 0, 0};
    int pixelIndex = 2;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}

TEST_F(OcclusionFillThreeVerticalPixelTests, ShouldReturnPixelValueOfPixelBelow)
{
    int image[3] = {0, 3, 0};
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}

TEST_F(OcclusionFillThreeVerticalPixelTests, ShouldReturnNearestAbove)
{
    int image[3] = {2, 3, 0};
    int pixelIndex = 2;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}

TEST_F(OcclusionFillThreeVerticalPixelTests, ShouldReturnNearestBelow)
{
    int image[3] = {0, 3, 2};
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}


class OcclusionFillThreePixelTests : public Test
{
public:
    int width = 3;
    int height = 1;
};

TEST_F(OcclusionFillThreePixelTests, ShouldReturnPixelValueOfRightMostPixel)
{
    int image[3] = {0, 0, 3};
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}

TEST_F(OcclusionFillThreePixelTests, ShouldReturnPixelValueOfRightSideOfZeroPixel)
{
    int image[3] = {0, 3, 0};
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}

TEST_F(OcclusionFillThreePixelTests, ShouldReturnNearestOnLeft)
{
    int image[3] = {2, 3, 0};
    int pixelIndex = 2;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}


TEST(OcclusionFillOnePixelTest, ShouldReturnPixelWith1GivenPixelWith0Value)
{
    int image[1] = {0};
    int width = 1;
    int height = 1;
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(1));
}


class OcclusionFillTwoPixelTests : public Test
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

class OcclusionFillTwoVerticalPixelTests : public Test
{
public:
    int width = 1;
    int height = 2;
};


TEST_F(OcclusionFillTwoVerticalPixelTests, ShouldReturnPixelValueOnTopOfZeroPixel)
{
    int image[2] = {2, 0};
    int pixelIndex = 1;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(2));
}

TEST_F(OcclusionFillTwoVerticalPixelTests, ShouldReturnPixelValueOnBottomOfZeroPixel)
{
    int image[2] = {0, 2};
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(2));
}

