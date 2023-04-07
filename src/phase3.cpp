#include "phase3.h"

    lodepng_wrapper::LodepngWrapper img0;

    int scaling_factor = 4;

    struct LoadImage : public IProgram
    {
        int run() override
        {
            unsigned error = img0.load_image("../../source-img/im0.png");
            error = img0.load_image2("../../source-img/im1.png");
            return (int) error;
        }
    };

    struct ResizeImage : public IProgram
    {
        int run() override
        {
            unsigned error = img0.resize_image(scaling_factor);
            error = img0.resize_image2(scaling_factor);
            return (int) error;
        }
    };
    
    struct TransformToGreyscale : public IProgram
    {
        int run() override
        {
            unsigned error = img0.transform_to_grayscale();
            error = img0.transform_to_grayscale2();
            return (int) error;
        }
    };

    struct SaveGreyscaleImage : public IProgram
    {
        int run() override
        {
            unsigned error = img0.save_greyimage("../../output-img/im0_grey.png");
            error = img0.save_greyimage2("../../output-img/im1_grey.png");
            return (int) error;
        }
    };

    struct SaveResizedImage : public IProgram
    {
        int run() override
        {
            unsigned error = img0.save_Resizedimage("../../output-img/im0_grey_resized.png");
            error = img0.save_Resizedimage2("../../output-img/im1_grey_resized.png");
            return (int) error;
        }
    };

    struct FilterResizedImage : public IProgram
    {
        int run() override
        {
            img0.apply_filter_resized(ZNCCFilter, 9, 1);
            unsigned error = img0.save_depthimage("../../output-img/im0_grf.png");

            img0.apply_filter_resized2(ZNCCFilter, 9, 2);
            error = img0.save_depthimage2("../../output-img/im1_grf.png");

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
    ResizeImage resizeImage;
    SaveResizedImage saveResizedImage;
    
    TransformToGreyscale transformToGreyscale;
    SaveGreyscaleImage saveGreyscaleImage;
    FilterResizedImage filterResizedImage;

    int result = Program_sw.runProgram(loadImage);
    std::cout << "Load image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(transformToGreyscale);
    std::cout << "Transform to greyscale return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(saveGreyscaleImage);
    std::cout << "Save greyscale image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(resizeImage);
    std::cout << "Resize image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(saveResizedImage);
    std::cout << "Save resized image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(filterResizedImage);
    std::cout << "Clone, filter and save resized image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    sw.saveEndPoint();
    std::cout << "Total elapsed time: " << sw.getElapsedTime() << " us\n" << std::endl;

    printPlatformProfile(false);
    return 0;
}
