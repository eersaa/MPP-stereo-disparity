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
    
    struct TransformToGreyscale : public IProgram
    {
        int run() override
        {
            unsigned error = img0.transform_to_grayscale();
            return (int) error;
        }
    };

    struct SaveGreyscaleImage : public IProgram
    {
        int run() override
        {
            unsigned error = img0.save_greyimage("../../output-img/im0_grey.png");
            return (int) error;
        }
    };

int main()
{
    // Measure total time
    ChronoClock clock;
    Stopwatch sw(clock);

    sw.saveStartPoint();
    
    // Step 3
    ProgramStopwatch Program_sw(clock);
    LoadImage loadImage;
    TransformToGreyscale transformToGreyscale;
    SaveGreyscaleImage saveGreyscaleImage;

    int result = Program_sw.runProgram(loadImage);
    std::cout << "Load image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(transformToGreyscale);
    std::cout << "Transform to greyscale return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(saveGreyscaleImage);
    std::cout << "Save greyscale image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    sw.saveEndPoint();
    std::cout << "Total elapsed time: " << sw.getElapsedTime() << " us" << std::endl;
    return 0;
}
