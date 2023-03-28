#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "opencl_base.h"

class OCL_Shrink : public OCL_Base
{
public:
    OCL_Shrink(/* args */)
    {
    }

    ~OCL_Shrink()
    {
        status = clReleaseMemObject(inputBuffer);
        status = clReleaseMemObject(outputBuffer);
    }

    void Run()
    {
    }

    void Shrink(unsigned char* image, unsigned char* shrunk_image, int width)
    {

        CreateInputBuffer(image, width);
        CreateOutputBuffer(width);
        
        cl_program prog = CreateProgramFromFile("grayscale.cl");
        CreateKernelFromProgram(prog, "shrink");

        status = clSetKernelArg(GetKernel(0), 0, sizeof(cl_mem), (void *)&inputBuffer);
        status = clSetKernelArg(GetKernel(0), 1, sizeof(cl_mem), (void *)&outputBuffer);

        status = clEnqueueNDRangeKernel(commandQueue, GetKernel(0), 1, NULL, 
                                            GetGlobalWorkSize(width), NULL, 0, NULL, NULL);

        status = clEnqueueReadBuffer(commandQueue, outputBuffer, CL_TRUE, 0, 
                            GetOutputBufferSize(width), shrunk_image, 0, NULL, NULL);

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

// class OCL_ShrinkTest : public ::testing::Test
// {
// public:
//     OCL_Shrink ocl_shrink;
//     unsigned char* image;
//     unsigned char* result_image;

//     // One byte per pixel
//     void createImage(int pixels)
//     {
//         image = (unsigned char*)malloc(pixels * sizeof(unsigned char));
//         for (int i = 0; i < pixels; i++)
//         {
//             image[i] = 1;
//         }
//     }

//     // Four bytes per pixel
//     void createRGBAImage(int pixels)
//     {
//         image = (unsigned char*)malloc(pixels * 4 * sizeof(unsigned char));
//         for (int i = 0; i < pixels; i++)
//         {
//             image[i] = 10;
//         }
//     }

// protected:
//     void TearDown() override
//     {
//         free(image);
//         free(result_image);
//     }

// };


// TEST_F(OCL_ShrinkTest, ShouldReturnOnePixelImageWhenGivenOnePixelImage)
// {
//     createImage(1);
//     result_image = (unsigned char*)malloc(1 * sizeof(unsigned char));
//     ocl_shrink.Shrink(image, result_image, 1);
//     ASSERT_THAT(result_image[0], Eq(1));
// }

// TEST_F(OCL_ShrinkTest, ShouldReturnOnePixelImageGivenFourPixelImage)
// {
//     createImage(4);
//     result_image = (unsigned char*)malloc(1 * sizeof(unsigned char));
//     ocl_shrink.Shrink(image, result_image, 4);
//     ASSERT_THAT(result_image[0], Eq(1));
// }

// TEST_F(OCL_ShrinkTest, ShouldReturnTwoPixelImageGivenEightPixelImage)
// {
//     createImage(8);
//     result_image = (unsigned char*)malloc(2 * sizeof(unsigned char));
//     ocl_shrink.Shrink(image, result_image, 8);
//     ASSERT_THAT(result_image[0], Eq(1));
//     ASSERT_THAT(result_image[1], Eq(1));
// }

class OCL_Grayscale : public OCL_Base
{
public:
    void Run() override
    {
    }

    void Convert_RGBA(unsigned char* image, unsigned char* result_image, int pixels)
    {

        cl_mem inputBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, 
                                pixels * 4 * sizeof(unsigned char), image, NULL);
        cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
                                 pixels * 4 * sizeof(unsigned char), NULL, NULL);
        
        cl_program prog = CreateProgramFromFile("grayscale.cl");
        CreateKernelFromProgram(prog, "grayscale_rgba");

        clSetKernelArg(GetKernel(0), 0, sizeof(cl_mem), (void *)&inputBuffer);
        clSetKernelArg(GetKernel(0), 1, sizeof(cl_mem), (void *)&outputBuffer);

        size_t global_work_size[1] = { pixels * 4 * sizeof(unsigned char) };
        clEnqueueNDRangeKernel(commandQueue, GetKernel(0), 1, NULL, 
                                            global_work_size, NULL, 0, NULL, NULL);

        clEnqueueReadBuffer(commandQueue, outputBuffer, CL_TRUE, 0, 
                            pixels * 4 * sizeof(unsigned char), result_image, 0, NULL, NULL);

    }
};

class OCL_GrayscaleOnePixelTests : public ::testing::Test
{
public:
    OCL_Grayscale ocl_grayscale;
    unsigned char image[4] = {0x72, 0x67, 0x62, 0xff}; // r = red, g = green, b = blue, a = alpha
    unsigned char* result_image;
    unsigned char grayscale;
    const int pixels = 1;

protected:
    void SetUp() override
    {
        result_image = (unsigned char*)malloc(4 * sizeof(unsigned char));
        grayscale = (unsigned char)(image[0] * 0.2126 + image[1] * 0.7152 + image[2] * 0.0722);
    }
    void TearDown() override
    {
        free(result_image);
    }
};

TEST_F(OCL_GrayscaleOnePixelTests, ShouldReplaceRedChannelWithGrayscaledRedChannel)
{
    ocl_grayscale.Convert_RGBA(image, result_image, pixels);
    ASSERT_THAT(result_image[0], Eq(grayscale));
}

TEST_F(OCL_GrayscaleOnePixelTests, ShouldReplaceGreenChannelWithGrayscaledGreenChannel)
{
    ocl_grayscale.Convert_RGBA(image, result_image, pixels);
    ASSERT_THAT(result_image[1], Eq(grayscale));
}

TEST_F(OCL_GrayscaleOnePixelTests, ShouldReplaceBlueChannelWithGrayscaledBlueChannel)
{
    ocl_grayscale.Convert_RGBA(image, result_image, pixels);
    ASSERT_THAT(result_image[2], Eq(grayscale));
}

TEST_F(OCL_GrayscaleOnePixelTests, ShouldKeepAlphaChannelTheSame)
{
    ocl_grayscale.Convert_RGBA(image, result_image, pixels);
    ASSERT_THAT(result_image[3], Eq(image[3]));
}

class OCL_GrayscaleTwoPixelTests : public ::testing::Test
{
public:
    OCL_Grayscale ocl_grayscale;
    unsigned char image[8] = {0x72, 0x67, 0x62, 0xff, 0x72, 0x67, 0x62, 0xff}; // r = red, g = green, b = blue, a = alpha * 2
    unsigned char* result_image;
    unsigned char grayscale;

protected:
    void SetUp() override
    {
        result_image = (unsigned char*)malloc(8 * sizeof(unsigned char));
        grayscale = (unsigned char)(image[0] * 0.2126 + image[1] * 0.7152 + image[2] * 0.0722);
    }
    void TearDown() override
    {
        free(result_image);
    }
};

TEST_F(OCL_GrayscaleTwoPixelTests, ShouldReplaceRGBChannelsWithGrayscaledChannels)
{
    int pixels = 2;
    ocl_grayscale.Convert_RGBA(image, result_image, pixels);
    EXPECT_THAT(result_image[4], Eq(grayscale));
    EXPECT_THAT(result_image[5], Eq(grayscale));
    EXPECT_THAT(result_image[6], Eq(grayscale));
}

TEST_F(OCL_GrayscaleTwoPixelTests, ShouldKeepAlphaChannelTheSame)
{
    int pixels = 2;
    ocl_grayscale.Convert_RGBA(image, result_image, pixels);
    EXPECT_THAT(result_image[7], Eq(image[7]));
}
