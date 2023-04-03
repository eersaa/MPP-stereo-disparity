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
}

unsigned LodepngWrapper::load_image(const char* filename)
{
    unsigned error = lodepng_decode32_file(&image, &width, &height, filename);
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

unsigned LodepngWrapper::save_greyimage(const char* filename)
{
    unsigned error = lodepng_encode_file(filename, grey_image, width, height, LCT_GREY, 8);
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

void LodepngWrapper::apply_filter(void (*filter)(unsigned char* image, unsigned width, unsigned height, unsigned windowSize), unsigned windowSize)
{
    filter(grey_image, width, height, windowSize);
}

unsigned LodepngWrapper::get_width()
{
    return width;
}

unsigned LodepngWrapper::get_height()
{
    return height;
}
