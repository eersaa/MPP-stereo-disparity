#include "phase1.h"

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

    struct ApplyFilter : public IProgram
    {
        int run() override
        {
            unsigned char * img0_fi = (unsigned char*)malloc(img0.get_width() * img0.get_height());
            img0.clone_image(img0_fi);

            unsigned char * img0_fo = (unsigned char*)malloc(img0.get_width() * img0.get_height());
            img0.clone_image(img0_fo);

            movingAvgFilter(img0_fo, img0_fi, img0.get_width(), img0.get_height(), 5);

            img0.set_image(img0_fo, img0.get_width(), img0.get_height(), GREY_CHANNELS);

            free(img0_fi);
            free(img0_fo);

            return 0;
        }
    };

    struct SaveGreyscaleImage : public IProgram
    {
        int run() override
        {
            unsigned error = img0.save_image("../../output-img/im0_grey.png");
            return (int) error;
        }
    };

    struct SaveFilteredImage : public IProgram
    {
        int run() override
        {
            unsigned error = img0.save_image("../../output-img/im0_grey_average_filtered.png");
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
    ApplyFilter applyFilter;
    SaveGreyscaleImage saveGreyscaleImage;
    SaveFilteredImage saveFilteredImage;

    int result = Program_sw.runProgram(loadImage);
    std::cout << "Load image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(transformToGreyscale);
    std::cout << "Transform to greyscale return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(saveGreyscaleImage);
    std::cout << "Save greyscale image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(applyFilter);
    std::cout << "Apply filter return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(saveFilteredImage);
    std::cout << "Save filtered image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    // result = Program_sw.runProgram(cloneAndSaveImage);
    // std::cout << "Clone and save image return result: " << result << std::endl;
    // std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    sw.saveEndPoint();
    std::cout << "Total elapsed time: " << sw.getElapsedTime() << " us\n" << std::endl;

    printPlatformProfile(false);
    return 0;
}
