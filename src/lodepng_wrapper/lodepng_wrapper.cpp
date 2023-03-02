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
}

unsigned LodepngWrapper::load_image(const char* filename)
{
    unsigned error = lodepng_decode32_file(&image, &width, &height, filename);
    if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    return error;
}

unsigned LodepngWrapper::save_image(const char* filename)
{
    unsigned error = lodepng_encode_file(filename, image, width, height, LCT_RGBA, 8);
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
    return 0;
}
