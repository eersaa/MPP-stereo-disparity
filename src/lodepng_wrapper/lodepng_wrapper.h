// Wrapper created based on the example from the lodepng library
#ifndef LODEPNG_WRAPPER_HPP
#define LODEPNG_WRAPPER_HPP

#include "lodepng.h"
#include <iostream>

namespace lodepng_wrapper
{

class LodepngWrapper
{
    public:
    LodepngWrapper();
    ~LodepngWrapper();

    unsigned load_image(const char* filename);
    unsigned save_image(const char* filename);
    unsigned transform_to_grayscale();

    private:
    unsigned char* image = 0;
    unsigned width, height;
};

} // namespace lodepng_wrapper

#endif // LODEPNG_WRAPPER_HPP
