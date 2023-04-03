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
    unsigned save_Resizedimage(const char* filename);
    unsigned transform_to_grayscale();
    void clone_greyimage(unsigned char* dest);
    void set_greyimage(unsigned char* src, unsigned width, unsigned height);
    void clone_resized_image(unsigned char* dest);
    void set_resized_image(unsigned char* src, unsigned width, unsigned height);
    void apply_filter(void (*filter)(unsigned char* image, unsigned width, unsigned height, unsigned windowSize), unsigned windowSize);
    void apply_filter_resized(void (*filter)(unsigned char* image, unsigned width, unsigned height, unsigned windowSize), unsigned windowSize);
    unsigned resize_image(unsigned scalingFactor);
    unsigned get_width();
    unsigned get_height();

    private:
    unsigned char* image = 0;
    unsigned char* grey_image = 0;
    unsigned char* resized_image = 0;
    unsigned width, height, resized_width, resized_height;
};

} // namespace lodepng_wrapper

#endif // LODEPNG_WRAPPER_HPP
