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
    unsigned load_image2(const char* filename2);
    unsigned save_RGBAimage(const char* filename);
    unsigned save_greyimage(const char* filename);
    unsigned save_greyimage2(const char* filename2);
    unsigned save_Resizedimage(const char* filename);
    unsigned save_Resizedimage2(const char* filename2);
    unsigned transform_to_grayscale();
    unsigned transform_to_grayscale2();
    void clone_greyimage(unsigned char* dest);
    void set_greyimage(unsigned char* src, unsigned width, unsigned height);
    void clone_resized_image(unsigned char* dest);
    void set_resized_image(unsigned char* src, unsigned width, unsigned height);
    void clone_resized_image2(unsigned char* dest2);
    void set_resized_image2(unsigned char* src2, unsigned width2, unsigned height2);
    void apply_filter(void (*filter)(unsigned char* image, unsigned width, unsigned height, unsigned windowSize), unsigned windowSize);
    void apply_filter_resized(void (*filter)(unsigned char* image, unsigned char* image2, unsigned width, unsigned height, unsigned windowSize), unsigned windowSize);
    unsigned resize_image(unsigned scalingFactor);
    unsigned resize_image2(unsigned scalingFactor2);
    unsigned get_width();
    unsigned get_height();

    private:
    unsigned char* image = 0;
    unsigned char* grey_image = 0;
    unsigned char* resized_image = 0;

    unsigned char* image2 = 0;
    unsigned char* grey_image2 = 0;
    unsigned char* resized_image2= 0;

    unsigned width, height, resized_width, resized_height;
    unsigned width2, height2, resized_width2, resized_height2;
};

} // namespace lodepng_wrapper

#endif // LODEPNG_WRAPPER_HPP
