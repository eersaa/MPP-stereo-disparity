#include "main.h"

    lodepng_wrapper::LodepngWrapper img0;

    struct LoadImage : public IProgram
    {
        int run() override
        {
            unsigned error = img0.load_image("../../source-img/im0.png");
            return (int) error;
        }
    };

int main()
{
    // Step 3
    ChronoClock clock;
    ProgramStopwatch LoadImage_sw(clock);
    LoadImage loadImage;

    int result = LoadImage_sw.runProgram(loadImage);
    std::cout << "Result: " << result << std::endl;
    std::cout << "Elapsed time: " << LoadImage_sw.getElapsedTime() << " us" << std::endl;
    return 0;
}
