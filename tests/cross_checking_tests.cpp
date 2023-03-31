#include <gmock/gmock.h>
#include <gtest/gtest.h>

void crossCheck(int iPixel1, int iPixel2, int oPixel)
{

}

TEST(CrossCheckingTests, ShouldReturnOutputPixelValueGivenTwoInputPixelValues)
{
    int iPixel1 = 0;
    int iPixel2 = 0;
    int oPixel = 0;
    crossCheck(iPixel1, iPixel2, oPixel);
}