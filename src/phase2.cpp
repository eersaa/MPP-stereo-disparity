#include "phase2.h"

    lodepng_wrapper::LodepngWrapper img0;
    lodepng_wrapper::LodepngWrapper img0_r;
    lodepng_wrapper::LodepngWrapper img0_1;

    lodepng_wrapper::LodepngWrapper img1;
    lodepng_wrapper::LodepngWrapper img1_r;
    lodepng_wrapper::LodepngWrapper img1_1;

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
            unsigned error = img0.resize_image(4);
            error = img0.resize_image2(4);
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
            unsigned char* dest_r = 0;
            unsigned char* dest_r2 = 0;
            unsigned width = img0.get_width();
            unsigned height = img0.get_height();

            unsigned resized_width = width / 4;
            unsigned resized_height = height / 4;

            dest_r = (unsigned char*) malloc(resized_width * resized_height * sizeof(unsigned char));
            img0.clone_resized_image(dest_r);
            img0_r.set_resized_image(dest_r, resized_width, resized_height);
            
            //dest_r2 = (unsigned char*) malloc(resized_width * resized_height * sizeof(unsigned char));
            //img1.clone_resized_image2(dest_r2);
            //img1_r.set_resized_image2(dest_r2, resized_width, resized_height);



            img0.apply_filter_resized(ZNCCFilter, 9);
            unsigned error = img0.save_Resizedimage("../../output-img/im0_grf.png");
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
