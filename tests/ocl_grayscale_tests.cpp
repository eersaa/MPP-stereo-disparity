#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "opencl_base.h"

class OCL_Grayscale : public OCL_Base
{
private:
    /* data */
public:
    OCL_Grayscale(/* args */)
    {
    }

    ~OCL_Grayscale()
    {
    }

    void Run()
    {
    }

    unsigned char Convert(unsigned char image)
    {
        return 0;
    }

};

TEST(OCL_GrayscaleTest, ShouldReturnOnePixelImageWhenGivenOnePixelImage)
{
    OCL_Grayscale ocl_grayscale;
    unsigned char image = 1;
    unsigned char greyscale_image = ocl_grayscale.Convert(image);
    ASSERT_THAT(greyscale_image, testing::Eq(1));
}

// TEST(OCL_GrayscaleTest, ShouldReturnEmptyImageWhenGivenEmptyImage)
// {
//     OCL_Grayscale ocl_grayscale;
//     unsigned char image = 0;
//     unsigned char greyscale_image = ocl_grayscale.Convert(image);
//     ASSERT_THAT(greyscale_image, testing::Eq(0));
// }