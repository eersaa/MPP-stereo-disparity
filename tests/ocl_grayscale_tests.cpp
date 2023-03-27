#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "opencl_base.h"

class OCL_Grayscale : public OCL_Base
{
public:
    OCL_Grayscale(/* args */)
    {
    }

    ~OCL_Grayscale()
    {
        status = clReleaseMemObject(inputBuffer);
        status = clReleaseMemObject(outputBuffer);
    }

    void Run()
    {
    }

    void Shrink(unsigned char* image, unsigned char* shrinked_image, int width)
    {

        CreateInputBuffer(image, width);
        CreateOutputBuffer(width);
        
        cl_program prog = CreateProgramFromFile("grayscale.cl");
        CreateKernelFromProgram(prog, "grayscale");

        status = clSetKernelArg(GetKernel(0), 0, sizeof(cl_mem), (void *)&inputBuffer);
        status = clSetKernelArg(GetKernel(0), 1, sizeof(cl_mem), (void *)&outputBuffer);

        status = clEnqueueNDRangeKernel(commandQueue, GetKernel(0), 1, NULL, 
                                            GetGlobalWorkSize(width), NULL, 0, NULL, NULL);

        status = clEnqueueReadBuffer(commandQueue, outputBuffer, CL_TRUE, 0, 
                            GetOutputBufferSize(width), shrinked_image, 0, NULL, NULL);

    }

    void Convert_R(unsigned char* image, unsigned char* grayscale_image, int width)
    {

        CreateInputBuffer(image, width);
        CreateOutputBuffer(width);
        
        cl_program prog = CreateProgramFromFile("grayscale.cl");
        CreateKernelFromProgram(prog, "grayscale_r");

        status = clSetKernelArg(GetKernel(0), 0, sizeof(cl_mem), (void *)&inputBuffer);
        status = clSetKernelArg(GetKernel(0), 1, sizeof(cl_mem), (void *)&outputBuffer);

        status = clEnqueueNDRangeKernel(commandQueue, GetKernel(0), 1, NULL, 
                                            GetGlobalWorkSize(width), NULL, 0, NULL, NULL);

        status = clEnqueueReadBuffer(commandQueue, outputBuffer, CL_TRUE, 0, 
                            GetOutputBufferSize(width), grayscale_image, 0, NULL, NULL);

    }

private:

    cl_mem CreateOutputBuffer(int width)
    {
        outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
                                GetOutputBufferSize(width), NULL, NULL);
        return outputBuffer;
    }

    cl_mem CreateInputBuffer(unsigned char* image, int width)
    {
        inputBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, 
                                width * sizeof(unsigned char), image, NULL);
        return inputBuffer;
    }

    size_t GetOutputBufferSize(int width)
    {
        size_t bufferSize = width/4 * sizeof(unsigned char);
        if (bufferSize < sizeof(unsigned char)) {bufferSize = sizeof(unsigned char);}
        return bufferSize;
    }

    size_t* GetGlobalWorkSize(int width)
    {
        global_work_size[0] = { width * sizeof(unsigned char) };
        return global_work_size;
    }

    cl_mem inputBuffer = nullptr;
    cl_mem outputBuffer = nullptr;

    size_t global_work_size[1];
};


using namespace testing;

class OCL_GrayscaleTest : public ::testing::Test
{
public:
    OCL_Grayscale ocl_grayscale;
    unsigned char* image;
    unsigned char* grayscale_image;

    // One byte per pixel
    void createImage(int pixels)
    {
        image = (unsigned char*)malloc(pixels * sizeof(unsigned char));
        for (int i = 0; i < pixels; i++)
        {
            image[i] = 1;
        }
    }

    // Four bytes per pixel
    void createRGBAImage(int pixels)
    {
        image = (unsigned char*)malloc(pixels * 4 * sizeof(unsigned char));
        for (int i = 0; i < pixels; i++)
        {
            image[i] = 10;
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
    ocl_grayscale.Shrink(image, grayscale_image, 1);
    ASSERT_THAT(grayscale_image[0], Eq(1));
}

TEST_F(OCL_GrayscaleTest, ShouldReturnOnePixelImageGivenFourPixelImage)
{
    createImage(4);
    grayscale_image = (unsigned char*)malloc(1 * sizeof(unsigned char));
    ocl_grayscale.Shrink(image, grayscale_image, 4);
    ASSERT_THAT(grayscale_image[0], Eq(1));
}

TEST_F(OCL_GrayscaleTest, ShouldReturnTwoPixelImageGivenEightPixelImage)
{
    createImage(8);
    grayscale_image = (unsigned char*)malloc(2 * sizeof(unsigned char));
    ocl_grayscale.Shrink(image, grayscale_image, 8);
    ASSERT_THAT(grayscale_image[0], Eq(1));
    ASSERT_THAT(grayscale_image[1], Eq(1));
}

TEST_F(OCL_GrayscaleTest, ShouldReturnGrayscalePixelOfRedPixelFromRGBAImage)
{
    createRGBAImage(1);
    grayscale_image = (unsigned char*)malloc(1 * sizeof(unsigned char));
    ocl_grayscale.Convert_R(image, grayscale_image, 4);
    ASSERT_THAT(*grayscale_image, Eq((unsigned char)(image[0] * 0.2126)));
}
