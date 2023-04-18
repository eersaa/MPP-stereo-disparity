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
    ASSERT_THAT(euclideanDistanceBetweenTwoPixels(pixel1Index, pixel2xIndex, pixel2yIndex, width), Eq(0));
}

class EuclideanDistance2x2ImageTests : public Test
{
public:
    int width = 2;
};

TEST_F(EuclideanDistance2x2ImageTests, ShouldReturnOneWhenPixel1IndexIsLastPixelAndPixel2IsFirst)
{
    int pixel1Index = 3;
    int pixel2xIndex = 0;
    int pixel2yIndex = 0;
    ASSERT_THAT(euclideanDistanceBetweenTwoPixels(pixel1Index, pixel2xIndex, pixel2yIndex, width), Eq(1));
}

TEST_F(EuclideanDistance2x2ImageTests, ShouldReturnOneWhenPixel1IndexIsFirstPixelAndPixel2IsLast)
{
    int pixel1Index = 0;
    int pixel2xIndex = 1;
    int pixel2yIndex = 1;
    ASSERT_THAT(euclideanDistanceBetweenTwoPixels(pixel1Index, pixel2xIndex, pixel2yIndex, width), Eq(1));
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
    unsigned char image[4] = {4, 0, 3, 2};
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
    unsigned char image[4] = {0, 4, 0, 0};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, 2, 2), Eq(4));
}

TEST_F(GetNearestFillPixelTwoByTwoImageFirstRowTests, ShouldReturnPixelValueOnLeft)
{
    unsigned char image[4] = {4, 0, 0, 0};
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
    unsigned char image[4] = {0, 0, 0, 4};
    int pixelIndex = 2;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(4));
}

TEST_F(GetNearestFillPixelTwoByTwoImageSecondRowTests, ShouldReturnPixelValueOnLeft)
{
    unsigned char image[4] = {0, 0, 4, 0};
    int pixelIndex = 3;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(4));
}


class GetNearestFillPixelThreeVerticalPixelTests : public Test
{
public:
    int width = 1;
    int height = 3;
};

TEST_F(GetNearestFillPixelThreeVerticalPixelTests, ShouldReturnPixelValueOfBottomPixel)
{
    unsigned char image[3] = {0, 0, 3};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}

TEST_F(GetNearestFillPixelThreeVerticalPixelTests, ShouldReturnPixelValueOfTopPixel)
{
    unsigned char image[3] = {3, 0, 0};
    int pixelIndex = 2;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}

TEST_F(GetNearestFillPixelThreeVerticalPixelTests, ShouldReturnPixelValueOfPixelBelow)
{
    unsigned char image[3] = {0, 3, 0};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}

TEST_F(GetNearestFillPixelThreeVerticalPixelTests, ShouldReturnNearestAbove)
{
    unsigned char image[3] = {2, 3, 0};
    int pixelIndex = 2;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}

TEST_F(GetNearestFillPixelThreeVerticalPixelTests, ShouldReturnNearestBelow)
{
    unsigned char image[3] = {0, 3, 2};
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
    unsigned char image[3] = {0, 0, 3};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}

TEST_F(GetNearestFillPixelThreePixelTests, ShouldReturnPixelValueOfRightSideOfZeroPixel)
{
    unsigned char image[3] = {0, 3, 0};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}

TEST_F(GetNearestFillPixelThreePixelTests, ShouldReturnNearestOnLeft)
{
    unsigned char image[3] = {2, 3, 0};
    int pixelIndex = 2;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(3));
}


TEST(GetNearestFillPixelOnePixelTest, ShouldReturnPixelWith1GivenPixelWith0Value)
{
    unsigned char image[1] = {0};
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
    unsigned char image[2] = {0, 2};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(2));
}

TEST_F(GetNearestFillPixelTwoPixelTests, ShouldReturnPixelValueOnLeftSideOfZeroPixel)
{
    unsigned char image[2] = {2, 0};
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
    unsigned char image[2] = {2, 0};
    int pixelIndex = 1;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(2));
}

TEST_F(GetNearestFillPixelTwoVerticalPixelTests, ShouldReturnPixelValueOnBottomOfZeroPixel)
{
    unsigned char image[2] = {0, 2};
    int pixelIndex = 0;
    ASSERT_THAT(getNearestFillPixelValue(pixelIndex, image, width, height), Eq(2));
}

TEST(FillZeroPixels1x3ImageTests, ShouldReturnAccessedPixelCountOf2)
{
    unsigned char image[3] = {3, 0, 0};
    int width = 3;
    int height = 1;
    ASSERT_THAT(fillZeroPixels(image, width, height), Eq(2));
}

TEST(FillZeroPixels1x3ImageTests, ShouldKeepExistingPixelValues)
{
    unsigned char image[3] = {1, 2, 3};
    int width = 3;
    int height = 1;
    fillZeroPixels(image, width, height);
    ASSERT_THAT(image, ElementsAre(1, 2, 3));
}

TEST(FillZeroPixels4x3ImageTests, ShouldFillAllZeroPixelsWithNearestNonZeroPixel)
{
    unsigned char image[12] = {10, 0, 0, 12, 11, 0, 0, 0, 12, 0, 0, 0};
    int width = 4;
    int height = 3;
    fillZeroPixels(image, width, height);
    // print table in 4x3 format
    for (int i = 0; i < width * height; i++)
    {
        if (i % width == 0)
        {
            std::cout << std::endl;
        }
        std::cout << (int)image[i] << " ";
    }
}
