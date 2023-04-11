#include <gmock/gmock.h>
#include <gtest/gtest.h>

int occlusionFill(int pixel_index, int *image, int width, int height)
{
    int fillPixelValue = 0;
    int pixelValue = 0;
    
    if (height > 1)
    {
        for (int y = 0; y < height; y++)
        {
            pixelValue = *(image + y * width);
            if (pixelValue != 0)
            {
                fillPixelValue = pixelValue;
                break;
            }
        }
    }
    else if (width > 1)
    {
        int distance = 0;
        int minDistance = width;

        for (int x = 0; x < width; x++)
        {
            distance = abs(pixel_index - x);
            pixelValue = *(image + x);

            if (pixelValue != 0
                && distance < minDistance)
            {
                minDistance = distance;
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

class OcclusionFillThreeVerticalPixelTests : public ::testing::Test
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

TEST_F(OcclusionFillThreeVerticalPixelTests, ShouldReturnPixelValueOfPixelBelow)
{
    int image[3] = {0, 3, 0};
    int pixelIndex = 0;
    ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
}

// TEST_F(OcclusionFillThreeVerticalPixelTests, ShouldReturnNearestOnTop)
// {
//     int image[3] = {2, 3, 0};
//     int pixelIndex = 2;
//     ASSERT_THAT(occlusionFill(pixelIndex, image, width, height), Eq(3));
// }


class OcclusionFillThreePixelTests : public ::testing::Test
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

class OcclusionFillTwoVerticalPixelTests : public ::testing::Test
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

