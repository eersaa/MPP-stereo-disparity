// Wrapper created based on the example from the lodepng library
#ifndef LODEPNG_WRAPPER_HPP
#define LODEPNG_WRAPPER_HPP

#include "lodepng.h"

namespace lodepng_wrapper
{

class LodepngWrapper
{
    public:
    LodepngWrapper();
    unsigned load_image(const std::string& filename);

    private:
    std::vector<unsigned char> image;
    unsigned width;
    unsigned height;
};

} // namespace lodepng_wrapper

#endif // LODEPNG_WRAPPER_HPP
