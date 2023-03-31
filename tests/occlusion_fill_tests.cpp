#include <gmock/gmock.h>
#include <gtest/gtest.h>

int occlusionFill(int pixel)
{
    return 0;
}


using namespace testing;

TEST(OcclusionFillTests, ShouldReturnPixelWith1GivenPixelWith0Value)
{
    int pixel = 0;
    ASSERT_THAT(occlusionFill(pixel), Eq(1));
}