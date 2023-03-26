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

    void Convert(unsigned char* image, unsigned char* grayscale_image, int width)
    {

        cl_mem inputBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, 
                                width * sizeof(unsigned char), image, NULL);

        size_t bufferSize = width/4 * sizeof(unsigned char);
        if (bufferSize < 1) {bufferSize = 1;}
        cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
                                bufferSize * sizeof(unsigned char), NULL, NULL);

        cl_program prog = CreateProgramFromFile("grayscale.cl");
        CreateKernelFromProgram(prog, "grayscale");

        status = clSetKernelArg(GetKernel(0), 0, sizeof(cl_mem), (void *)&inputBuffer);
        status = clSetKernelArg(GetKernel(0), 1, sizeof(cl_mem), (void *)&outputBuffer);

        size_t global_work_size[1] = { width * sizeof(unsigned char) };
        status = clEnqueueNDRangeKernel(commandQueue, GetKernel(0), 1, NULL, 
                                            global_work_size, NULL, 0, NULL, NULL);

        status = clEnqueueReadBuffer(commandQueue, outputBuffer, CL_TRUE, 0, 
                            bufferSize * sizeof(unsigned char), grayscale_image, 0, NULL, NULL);
    }

};

using namespace testing;

class OCL_GrayscaleTest : public ::testing::Test
{
public:
    OCL_Grayscale ocl_grayscale;
    unsigned char* image;
    unsigned char* grayscale_image;

    void createImage(int size)
    {
        image = (unsigned char*)malloc(size * sizeof(unsigned char));
        for (int i = 0; i < size; i++)
        {
            image[i] = 1;
        }
    }

protected:
    void TearDown() override
    {
        free(image);
        free(grayscale_image);
    }

};


TEST_F(OCL_GrayscaleTest, ShouldReturnOnePixelImageWhenGivenOnePixelImage)
{
    createImage(1);
    grayscale_image = (unsigned char*)malloc(1 * sizeof(unsigned char));
    ocl_grayscale.Convert(image, grayscale_image, 1);
    ASSERT_THAT(*grayscale_image, Eq(1));
}

TEST_F(OCL_GrayscaleTest, ShouldReturnOnePixelImageGivenFourPixelImage)
{
    createImage(4);
    grayscale_image = (unsigned char*)malloc(1 * sizeof(unsigned char));
    ocl_grayscale.Convert(image, grayscale_image, 4);
    ASSERT_THAT(*grayscale_image, Eq(1));
}

TEST_F(OCL_GrayscaleTest, ShouldReturnTwoPixelImageGivenEightPixelImage)
{
    createImage(8);
    grayscale_image = (unsigned char*)malloc(2 * sizeof(unsigned char));
    ocl_grayscale.Convert(image, grayscale_image, 8);
    ASSERT_THAT(*grayscale_image, Eq(1));
    ASSERT_THAT(*(grayscale_image + 1), Eq(1));
}
