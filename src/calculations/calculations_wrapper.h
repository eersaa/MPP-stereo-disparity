// Wrapper created based on the example from the lodepng library
#ifndef CALCULATIONS_WRAPPER_HPP
#define CALCULATIONS_WRAPPER_HPP

#include <iostream>

namespace calculations_wrapper
{

class calculationsWrapper
{
    public:
    CalculationsWrapper();
    ~CalculationsWrapper();

    unsigned calc_zncc();

    private:
    unsigned char* image = 0;
    unsigned char* grey_image = 0;
    unsigned width, height;
};

} // namespace lodepng_wrapper

#endif // LODEPNG_WRAPPER_HPP