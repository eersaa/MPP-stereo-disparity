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
    unsigned save_RGBAimage(const char* filename);
    unsigned save_greyimage(const char* filename);
    unsigned transform_to_grayscale();
    void clone_greyimage(unsigned char* dest, unsigned *width, unsigned *height);

    private:
    unsigned char* image = 0;
    unsigned char* grey_image = 0;
    unsigned width, height;
};

} // namespace lodepng_wrapper

#endif // LODEPNG_WRAPPER_HPP
