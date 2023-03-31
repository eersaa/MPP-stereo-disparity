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

unsigned LodepngWrapper::resize_image()
{
    //zncc algorithm
    for (int j = 0; j < imHeight; j++) {
        for (int i = 0; i < imWidth; i++) {
            for (int d = 0; d < maxDisp; d++) {
                for (int y = 0; y < winSize; y++) {
                    for (int x = 0; x < winSize; x++) {
                        //Calculate the mean value for each window
                        windowSum = windowSum + image[j+4-y][i+4-x];
                        windowSum2 = windowSum2 + image2[j+4-y][i+4-x];
                    }   
                }
                windowMean = windowSum / (imWidth * imHeight);
                windowMean2 = windowSum2 / (imWidth * imHeight);

                //Calculate stdev for each window
                for (int y = 0; y < winSize; y++) {
                    for (int x = 0; x < winSize; x++) {
                        windowstd = windowstd + image[j+4-y][i+4-x];
                        windowstd2 = windowstd2 + image2[j+4-y][i+4-x];
                    }   
                }
                windowstd = (pow(windowstd, 0.5)) / (2 * winSize + 1);
                windowstd2 = (pow(windowstd2, 0.5)) / (2 * winSize + 1);

                for (int y = 0; y < winSize; j++) {
                    for (int x = 0; x < imWidth; j++) {
                        //calculate the zncc value for each window
                    znccVal = znccVal + (image[j+4-y][i+4-x] - windowMean) * (image[j+4-y][i+4-x] - windowMean2);
                    }
                }
                znccVal = znccVal / (pow((2 * winSize + 1), 2) * windowstd * windowstd2);

                if (znccVal > currentMaxSum) {
                    currentMaxSum = znccVal;
                    bestDispVal = znccVal;
                }
            }
            int disparity_image_pixel = bestDispVal;
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
