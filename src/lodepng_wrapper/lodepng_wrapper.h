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
    unsigned save_depthimage(const char* filename);
    unsigned save_depthimage2(const char* filename2);
    unsigned save_image(const char* filename, int savedImageID, int imWidth, int imHeight, int saveType);
    unsigned transform_to_grayscale();
    unsigned transform_to_grayscale2();
    void clone_image(unsigned char* dest);
    void clone_greyimage(unsigned char* dest);
    void set_image(unsigned char* src, unsigned width, unsigned height);
    void set_greyimage(unsigned char* src, unsigned width, unsigned height);
    void apply_filter(void (*filter)(unsigned char* image, unsigned width, unsigned height, unsigned windowSize), unsigned windowSize);
    void apply_filter_resized(void (*filter)(unsigned char* imageOut, unsigned char* image, unsigned char* image2, unsigned width, unsigned height, unsigned windowSize, unsigned leftToRight), unsigned windowSize, unsigned leftToRight);
    void apply_filter_resized2(void (*filter)(unsigned char* imageOut, unsigned char* image, unsigned char* image2, unsigned width, unsigned height, unsigned windowSize, unsigned leftToRight), unsigned windowSize, unsigned leftToRight);
    void crossCheck(void (*filter)(unsigned char *image1, unsigned char *image2, int threshold, unsigned char *outputImage, int imageSize));
    void occlusion_fill(void (*filter)(unsigned char *image, unsigned char *outImage, int width, int height));
    unsigned resize_image(unsigned scalingFactor);
    unsigned resize_image2(unsigned scalingFactor2);
    unsigned get_width();
    unsigned get_height();

    private:
    unsigned char* image = 0;
    unsigned char* grey_image = 0;
    unsigned char* resized_image = 0;
    unsigned char* depth_image = 0;

    unsigned char* crossCheck_image = 0;
    unsigned char* occlusion_fill_image = 0;

    unsigned char* image2 = 0;
    unsigned char* grey_image2 = 0;
    unsigned char* resized_image2= 0;
    unsigned char* depth_image2= 0;

    unsigned width, height, resized_width, resized_height;
    unsigned width2, height2, resized_width2, resized_height2;
};

} // namespace lodepng_wrapper

#endif // LODEPNG_WRAPPER_HPP
