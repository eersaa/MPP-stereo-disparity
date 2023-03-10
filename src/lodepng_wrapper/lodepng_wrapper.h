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
    void clone_greyimage(unsigned char* dest);
    void set_greyimage(unsigned char* src, unsigned width, unsigned height);
    void apply_filter(void (*filter)(unsigned char* image, unsigned width, unsigned height, unsigned windowSize), unsigned windowSize);
    unsigned get_width();
    unsigned get_height();

    private:
    unsigned char* image = 0;
    unsigned char* grey_image = 0;
    unsigned width, height;
};

} // namespace lodepng_wrapper

#endif // LODEPNG_WRAPPER_HPP
