#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "opencl_base.h"

class OCL_Grayscale : public OCL_Base
{
private:
    /* data */
public:
    OCL_Grayscale(/* args */);
    ~OCL_Grayscale();

    void Run() override;
};

OCL_Grayscale::OCL_Grayscale(/* args */)
{
}

OCL_Grayscale::~OCL_Grayscale()
{
}

void OCL_Grayscale::Run()
{
}


TEST(OCL_GrayscaleTest, ShouldReturnEmptyImageWhenGivenEmptyImage)
{
    OCL_Grayscale ocl_grayscale;

}