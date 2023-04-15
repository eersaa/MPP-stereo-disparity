#include "occlusion_fill.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

TEST(EuclideanDistanceTests, ShouldReturnZeroWhenPixelIsOnSamePosition)
{
    int pixel1Index = 0;
    int pixel2xIndex = 0;
    int pixel2yIndex = 0;
    int width = 1;
    int height = 1;
    ASSERT_THAT(euclideanDistanceBetweenTwoPixels(pixel1Index, pixel2xIndex, pixel2yIndex, width, height), Eq(0));
}

class EuclideanDistance2x2ImageTests : public Test
{
public:
    int width = 2;
    int height = 2;
};

TEST_F(EuclideanDistance2x2ImageTests, ShouldReturnOneWhenPixel1IndexIsLastPixelAndPixel2IsFirst)
{
    int pixel1Index = 3;
    int pixel2xIndex = 0;
    int pixel2yIndex = 0;
    ASSERT_THAT(euclideanDistanceBetweenTwoPixels(pixel1Index, pixel2xIndex, pixel2yIndex, width, height), Eq(1));
}

TEST_F(EuclideanDistance2x2ImageTests, ShouldReturnOneWhenPixel1IndexIsFirstPixelAndPixel2IsLast)
{
    int pixel1Index = 0;
    int pixel2xIndex = 1;
    int pixel2yIndex = 1;
    ASSERT_THAT(euclideanDistanceBetweenTwoPixels(pixel1Index, pixel2xIndex, pixel2yIndex, width, height), Eq(1));
}

class HorizontalDistanceOneRowTests : public Test
{
public:
    int width = 3;
};

TEST_F(HorizontalDistanceOneRowTests, ShouldReturnZeroWhenPixelIsOnSameColumn)
{
    int pixelIndex = 0;
    int columnIndex = 0;
    ASSERT_THAT(horDistance(pixelIndex, columnIndex, width), Eq(0));
}

TEST_F(HorizontalDistanceOneRowTests, ShouldReturnTwoWhenPixelIsTwoColumnsRight)
{
    int pixelIndex = 2;
    int columnIndex = 0;
    ASSERT_THAT(horDistance(pixelIndex, columnIndex, width), Eq(2));
}

TEST_F(HorizontalDistanceOneRowTests, ShouldReturnTwoWhenPixelIsTwoColumnsLeft)
{
    int pixelIndex = 0;
    int columnIndex = 2;
    ASSERT_THAT(horDistance(pixelIndex, columnIndex, width), Eq(2));
}

TEST(HorizontalDistanceOneColumnTests, ShouldReturnZeroWhenPixelInSameColumnButOnNextRow)
{
    int pixelIndex = 1;
    int columnIndex = 0;
    int width = 1;
    ASSERT_THAT(horDistance(pixelIndex, columnIndex, width), Eq(0));
}

TEST(HorizontalDistance2x2ImageTests, ShouldReturnZeroWhenPixelIsOnSecondRowOnSameColumn)
{
    int pixelIndex = 2;
    int columnIndex = 0;
    int width = 2;
    ASSERT_THAT(horDistance(pixelIndex, columnIndex, width), Eq(0));
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

TEST_F(VerticalDistance2x2ImageTests, ShouldReturnZeroWhenPixelAndRowIndexAreOnSecondRow)
{
    int pixelIndex = 2;
    int rowIndex = 1;
    ASSERT_THAT(verDistance(pixelIndex, rowIndex, width), Eq(0));
}


TEST(GetNearestFillPixelTwoByTwoImageTests, ShouldReturnNearestOnLeft)
{
    int image[4] = {4, 0, 3, 2};
    int pixelIndex = 1;
    int width = 2;
    int height = 2;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(4));
}


class GetNearestFillPixelTwoByTwoImageFirstRowTests : public Test
{
public:
    int width = 2;
    int height = 2;
};

TEST_F(GetNearestFillPixelTwoByTwoImageFirstRowTests, ShouldReturnPixelValueOnRight)
{
    int image[4] = {0, 4, 0, 0};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, 2, 2), Eq(4));
}

TEST_F(GetNearestFillPixelTwoByTwoImageFirstRowTests, ShouldReturnPixelValueOnLeft)
{
    int image[4] = {4, 0, 0, 0};
    int pixelIndex = 1;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, 2, 2), Eq(4));
}

class GetNearestFillPixelTwoByTwoImageSecondRowTests : public Test
{
public:
    int width = 2;
    int height = 2;
};

TEST_F(GetNearestFillPixelTwoByTwoImageSecondRowTests, ShouldReturnPixelValueOnRight)
{
    int image[4] = {0, 0, 0, 4};
    int pixelIndex = 2;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(4));
}

TEST_F(GetNearestFillPixelTwoByTwoImageSecondRowTests, ShouldReturnPixelValueOnLeft)
{
    int image[4] = {0, 0, 4, 0};
    int pixelIndex = 3;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(4));
}

// TEST_F(GetNearestFillPixelTwoByTwoImageSecondRowTests, ShouldReturnSameValueAsInIndex2)
// {
//     int image[4] = {4, 0, 3, 0};
//     int pixelIndex = 2;
//     ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
// }


class GetNearestFillPixelThreeVerticalPixelTests : public Test
{
public:
    int width = 1;
    int height = 3;
};

TEST_F(GetNearestFillPixelThreeVerticalPixelTests, ShouldReturnPixelValueOfBottomPixel)
{
    int image[3] = {0, 0, 3};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}

TEST_F(GetNearestFillPixelThreeVerticalPixelTests, ShouldReturnPixelValueOfTopPixel)
{
    int image[3] = {3, 0, 0};
    int pixelIndex = 2;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}

TEST_F(GetNearestFillPixelThreeVerticalPixelTests, ShouldReturnPixelValueOfPixelBelow)
{
    int image[3] = {0, 3, 0};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}

TEST_F(GetNearestFillPixelThreeVerticalPixelTests, ShouldReturnNearestAbove)
{
    int image[3] = {2, 3, 0};
    int pixelIndex = 2;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}

TEST_F(GetNearestFillPixelThreeVerticalPixelTests, ShouldReturnNearestBelow)
{
    int image[3] = {0, 3, 2};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}


class GetNearestFillPixelThreePixelTests : public Test
{
public:
    int width = 3;
    int height = 1;
};

TEST_F(GetNearestFillPixelThreePixelTests, ShouldReturnPixelValueOfRightMostPixel)
{
    int image[3] = {0, 0, 3};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}

TEST_F(GetNearestFillPixelThreePixelTests, ShouldReturnPixelValueOfRightSideOfZeroPixel)
{
    int image[3] = {0, 3, 0};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}

TEST_F(GetNearestFillPixelThreePixelTests, ShouldReturnNearestOnLeft)
{
    int image[3] = {2, 3, 0};
    int pixelIndex = 2;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}


TEST(GetNearestFillPixelOnePixelTest, ShouldReturnPixelWith1GivenPixelWith0Value)
{
    int image[1] = {0};
    int width = 1;
    int height = 1;
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(1));
}


class GetNearestFillPixelTwoPixelTests : public Test
{
public:
    int width = 2;
    int height = 1;
};

TEST_F(GetNearestFillPixelTwoPixelTests, ShouldReturnPixelValueOnRightSideOfZeroPixel)
{
    int image[2] = {0, 2};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(2));
}

TEST_F(GetNearestFillPixelTwoPixelTests, ShouldReturnPixelValueOnLeftSideOfZeroPixel)
{
    int image[2] = {2, 0};
    int pixelIndex = 1;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(2));
}

class GetNearestFillPixelTwoVerticalPixelTests : public Test
{
public:
    int width = 1;
    int height = 2;
};


TEST_F(GetNearestFillPixelTwoVerticalPixelTests, ShouldReturnPixelValueOnTopOfZeroPixel)
{
    int image[2] = {2, 0};
    int pixelIndex = 1;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(2));
}

TEST_F(GetNearestFillPixelTwoVerticalPixelTests, ShouldReturnPixelValueOnBottomOfZeroPixel)
{
    int image[2] = {0, 2};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(2));
}

TEST(FillZeroPixels3x3ImageTests, ShouldFillAllZeroPixelsWithNearestNonZeroPixel)
{
    int image[9] = {9, 10, 11, 10, 0, 0, 11, 0, 0};
    int width = 3;
    int height = 3;
    fillZeroPixels(image, width, height);
    // print table in 3x3 format
    for (int i = 0; i < 9; i++)
    {
        std::cout << image[i] << " ";
        if ((i + 1) % 3 == 0)
        {
            std::cout << std::endl;
        }
    }
}
