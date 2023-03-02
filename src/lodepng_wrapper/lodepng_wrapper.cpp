// Wrapper created based on the example from the lodepng library
#include "lodepng_wrapper.h"

using namespace lodepng_wrapper;

LodepngWrapper::LodepngWrapper()
{
    ;
}

LodepngWrapper::~LodepngWrapper()
{
    free(image));
}

unsigned LodepngWrapper::load_image(const char* filename)
{
    unsigned error = lodepng_decode32_file(&image, &width, &height, filename);
    if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    return error;
}
