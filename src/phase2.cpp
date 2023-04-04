#include "phase2.h"

    lodepng_wrapper::LodepngWrapper img0;
    lodepng_wrapper::LodepngWrapper img0_r;
    lodepng_wrapper::LodepngWrapper img0_1;

    struct LoadImage : public IProgram
    {
        int run() override
        {
            unsigned error = img0.load_image("../../source-img/im0.png");
            return (int) error;
        }
    };

    struct ResizeImage : public IProgram
    {
        int run() override
        {
            unsigned error = img0.resize_image(4);
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
            img0.apply_filter(movingAvgFilter, 5);
            return 0;
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

    struct SaveResizedImage : public IProgram
    {
        int run() override
        {
            unsigned error = img0.save_Resizedimage("../../output-img/im0_grey_resized.png");
            return (int) error;
        }
    };

    struct FilterResizedImage : public IProgram
    {
        int run() override
        {
            unsigned char* dest_r = 0;
            unsigned width = img0.get_width();
            unsigned height = img0.get_height();

            unsigned resized_width = width / 4;
            unsigned resized_height = height / 4;

            dest_r = (unsigned char*) malloc(resized_width * resized_height * sizeof(unsigned char));
            img0.clone_resized_image(dest_r);
            img0_r.set_resized_image(dest_r, resized_width, resized_height);
            img0_r.apply_filter_resized(ZNCCFilter, 9);
            unsigned error = img0_r.save_Resizedimage("../../output-img/im0_grf.png");
            return (int) error;
        }
    };

    struct CloneAndSaveImage : public IProgram
    {
        int run() override
        {
            unsigned char* dest = 0;
            unsigned width = img0.get_width();
            unsigned height = img0.get_height();
            dest = (unsigned char*) malloc(width * height * sizeof(unsigned char));
            img0.clone_greyimage(dest);
            img0_1.set_greyimage(dest, width, height);
            img0_1.apply_filter(movingAvgFilter, 30);
            unsigned error = img0_1.save_greyimage("../../output-img/im0_1_grey.png");
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
    ApplyFilter applyFilter;
    SaveGreyscaleImage saveGreyscaleImage;
    CloneAndSaveImage cloneAndSaveImage;
    FilterResizedImage filterResizedImage;

    int result = Program_sw.runProgram(loadImage);
    std::cout << "Load image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(transformToGreyscale);
    std::cout << "Transform to greyscale return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(resizeImage);
    std::cout << "Resize image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(applyFilter);
    std::cout << "Apply filter return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(saveGreyscaleImage);
    std::cout << "Save greyscale image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(saveResizedImage);
    std::cout << "Save resized image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(filterResizedImage);
    std::cout << "Clone, filter and save resized image return result: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

     result = Program_sw.runProgram(cloneAndSaveImage);
     std::cout << "Clone and save image return result: " << result << std::endl;
     std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    sw.saveEndPoint();
    std::cout << "Total elapsed time: " << sw.getElapsedTime() << " us\n" << std::endl;

    printPlatformProfile(false);
    return 0;
}
