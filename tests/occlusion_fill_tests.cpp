#include <gmock/gmock.h>
#include <gtest/gtest.h>

int occlusionFill(int pixel)
{
    if (pixel == 0)
    {
        return 1;
    }
    return 0;
}


using namespace testing;

TEST(OcclusionFillTests, ShouldReturnPixelWith1GivenOnePixelWith0Value)
{
    int pixel = 0;
    ASSERT_THAT(occlusionFill(pixel), Eq(1));
}