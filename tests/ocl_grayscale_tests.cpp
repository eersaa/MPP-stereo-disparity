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

        cl_mem inputBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, 
                                sizeof(unsigned char), &image, NULL);
        cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
                                sizeof(unsigned char), NULL, NULL);

        cl_program prog = CreateProgramFromFile("grayscale.cl");
        CreateKernelFromProgram(prog, "grayscale");

        status = clSetKernelArg(GetKernel(0), 0, sizeof(cl_mem), (void *)&inputBuffer);
        status = clSetKernelArg(GetKernel(0), 1, sizeof(cl_mem), (void *)&outputBuffer);

        size_t global_work_size[1] = { sizeof(unsigned char) };
        status = clEnqueueNDRangeKernel(commandQueue, GetKernel(0), 1, NULL, 
                                            global_work_size, NULL, 0, NULL, NULL);

        unsigned char grayscale_image = 0;
        status = clEnqueueReadBuffer(commandQueue, outputBuffer, CL_TRUE, 0, 
                            sizeof(unsigned char), &grayscale_image, 0, NULL, NULL);

        return grayscale_image;
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