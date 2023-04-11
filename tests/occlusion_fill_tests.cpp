#include <gmock/gmock.h>
#include <gtest/gtest.h>

int distance(int pixel_index, int index)
{
    return abs(pixel_index - index);
}

double euclideanDistance(int pixel_index, int x_index, int y_index)
{
    return sqrt(pow(distance(pixel_index, x_index), 2) + pow(distance(pixel_index, y_index), 2));
}

int occlusionFill(int pixel_index, int *image, int width, int height)
{
    int fillPixelValue = 0;
    int pixelValue = 0;

    double minDist = width + height;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double dist = euclideanDistance(pixel_index, x, y);
            pixelValue = *(image + x + y * width);

            if (pixelValue != 0
                && dist < minDist)
            {
                minDist = dist;
                fillPixelValue = pixelValue;
            }
        }
    }    
    
    if (fillPixelValue == 0)
    {
        fillPixelValue = 1;
    }
    return fillPixelValue;
}

using namespace testing;

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

TEST(OcclusionFillTwoByTwoImageSecondRowTests, ShouldReturnPixelValueOnRight)
{
    int image[4] = {0, 0, 0, 4};
    int pixelIndex = 2;
    ASSERT_THAT(occlusionFill(pixelIndex, image, 2, 2), Eq(4));
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

