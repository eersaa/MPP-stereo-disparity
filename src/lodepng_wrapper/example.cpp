#include "lodepng_wrapper.h"

int main()
{
    lodepng_wrapper::LodepngWrapper img0;
    unsigned error = img0.load_image("../../../source-img/im0.png");
    return (int) error;
}
