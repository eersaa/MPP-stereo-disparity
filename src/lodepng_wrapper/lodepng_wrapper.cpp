// Wrapper created based on the example from the lodepng library
#include "lodepng_wrapper.h"

using namespace lodepng_wrapper;

LodepngWrapper::LodepngWrapper()
{
    ;
}

LodepngWrapper::~LodepngWrapper()
{
    free(image);
    free(grey_image);
    free(resized_image);
    free(image2);
    free(grey_image2);
    free(resized_image2);
}

unsigned LodepngWrapper::load_image(const char* filename)
{
    unsigned error = lodepng_decode32_file(&image, &width, &height, filename);
    if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    return error;
}

unsigned LodepngWrapper::load_image2(const char* filename2)
{
    unsigned error = lodepng_decode32_file(&image2, &width2, &height2, filename2);
    if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    return error;
}

unsigned LodepngWrapper::save_RGBAimage(const char* filename)
{
    unsigned error = lodepng_encode_file(filename, image, width, height, LCT_RGBA, 8);
    if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    return error;
}

unsigned LodepngWrapper::save_Resizedimage(const char* filename)
{
    unsigned error = lodepng_encode_file(filename, resized_image, resized_width, resized_height, LCT_GREY, 8);
    if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    return error;
}

unsigned LodepngWrapper::save_Resizedimage2(const char* filename2)
{
    unsigned error = lodepng_encode_file(filename2, resized_image2, resized_width2, resized_height2, LCT_GREY, 8);
    if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    return error;
}

unsigned LodepngWrapper::save_greyimage(const char* filename)
{
    unsigned error = lodepng_encode_file(filename, grey_image, width, height, LCT_GREY, 8);
    if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    return error;
}

unsigned LodepngWrapper::save_greyimage2(const char* filename2)
{
    unsigned error = lodepng_encode_file(filename2, grey_image2, width2, height2, LCT_GREY, 8);
    if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    return error;
}

unsigned LodepngWrapper::transform_to_grayscale()
{
    // transform image buffer to greyscale with following formula: Y=0.2126R+0.7152G+0.0722B
    for (unsigned i = 0; i < width * height * 4; i += 4)
    {
        unsigned char r = image[i];
        unsigned char g = image[i + 1];
        unsigned char b = image[i + 2];
        unsigned char y = (unsigned char)(0.2126 * r + 0.7152 * g + 0.0722 * b);
        image[i] = y;
        image[i + 1] = y;
        image[i + 2] = y;
    }

    // shrink the buffer to only contain the Y channel
    grey_image = (unsigned char*)malloc(width * height);
    for (unsigned i = 0; i < width * height * 4; i += 4)
    {
        grey_image[i / 4] = image[i];
    }

    return 0;
}

unsigned LodepngWrapper::transform_to_grayscale2()
{
    // transform image buffer to greyscale with following formula: Y=0.2126R+0.7152G+0.0722B
    for (unsigned i = 0; i < width2 * height2 * 4; i += 4)
    {
        unsigned char r = image2[i];
        unsigned char g = image2[i + 1];
        unsigned char b = image2[i + 2];
        unsigned char y = (unsigned char)(0.2126 * r + 0.7152 * g + 0.0722 * b);
        image2[i] = y;
        image2[i + 1] = y;
        image2[i + 2] = y;
    }

    // shrink the buffer to only contain the Y channel
    grey_image2 = (unsigned char*)malloc(width2 * height2);
    for (unsigned i = 0; i < width2 * height2 * 4; i += 4)
    {
        grey_image2[i / 4] = image2[i];
    }

    return 0;
}

void LodepngWrapper::clone_greyimage(unsigned char* dest)
{
    memcpy(dest, grey_image, this->width * this->height);
}

void LodepngWrapper::set_greyimage(unsigned char* src, unsigned width, unsigned height)
{
    this->width = width;
    this->height = height;
    grey_image = (unsigned char*)malloc(width * height);
    memcpy(grey_image, src, width * height);
}

unsigned LodepngWrapper::resize_image(unsigned scalingFactor)
{
    //int scalingFactor = 4;
    resized_width = width / scalingFactor;
    resized_height = height / scalingFactor;
    
    // shrink the image
    resized_image = (unsigned char*)malloc(resized_width * resized_height);

    unsigned int ind = 0;
    unsigned int currow = 0;
    for (unsigned i = 0; i < (resized_width * resized_height); i++)
    {   
        resized_image[i] = grey_image[ind];
        ind = ind + scalingFactor;
        if (ind >= (width + (currow * width))) {
            currow = currow + scalingFactor;
            ind = (currow * width);
        }
    }

    return 0;
}

unsigned LodepngWrapper::resize_image2(unsigned scalingFactor2)
{
    //int scalingFactor = 4;
    resized_width2 = width2 / scalingFactor2;
    resized_height2 = height2 / scalingFactor2;
    
    // shrink the image
    resized_image2 = (unsigned char*)malloc(resized_width2 * resized_height2);

    unsigned int ind = 0;
    unsigned int currow = 0;
    for (unsigned i = 0; i < (resized_width2 * resized_height2); i++)
    {   
        resized_image2[i] = grey_image2[ind];
        ind = ind + scalingFactor2;
        if (ind >= (width2 + (currow * width2))) {
            currow = currow + scalingFactor2;
            ind = (currow * width2);
        }
    }

    return 0;
}

void LodepngWrapper::clone_resized_image(unsigned char* dest)
{
    memcpy(dest, resized_image, this->resized_width * this->resized_height);
}

void LodepngWrapper::set_resized_image(unsigned char* src, unsigned resized_width, unsigned resized_height)
{
    this->resized_width = resized_width;
    this->resized_height = resized_height;
    resized_image = (unsigned char*)malloc(resized_width * resized_height);
    memcpy(resized_image, src, resized_width * resized_height);
}

void LodepngWrapper::apply_filter(void (*filter)(unsigned char* image, unsigned width, unsigned height, unsigned windowSize), unsigned windowSize)
{
    filter(grey_image, width, height, windowSize);
}

void LodepngWrapper::apply_filter_resized(void (*filter)(unsigned char* image, unsigned char* image2, unsigned width, unsigned height, unsigned windowSize), unsigned windowSize)
{
    filter(resized_image, resized_image2, resized_width, resized_height, windowSize);
}

unsigned LodepngWrapper::get_width()
{
    return width;
}

unsigned LodepngWrapper::get_height()
{
    return height;
}
