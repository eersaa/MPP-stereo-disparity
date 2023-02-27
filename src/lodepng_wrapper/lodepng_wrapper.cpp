// Wrapper created based on the example from the lodepng library
#include "lodepng_wrapper.h"

using namespace lodepng_wrapper;

LodepngWrapper::LodepngWrapper()
{
    ;
}

unsigned LodepngWrapper::load_image(const std::string& filename)
{
    return lodepng::decode(image, width, height, filename);
}
