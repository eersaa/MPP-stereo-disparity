#include "phase4.h"

int scaling_factor = 4;

class OCL_image : public OCL_Base, public lodepng_wrapper::LodepngWrapper
{
public:
    OCL_image() : OCL_Base()
    {
    }

    ~OCL_image()
    {
        clReleaseMemObject(outputBuffer);
    }

    void Run() override
    {
    }

    unsigned transform_to_grayscale() override
    {
        cl_mem inputBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                            _width * _height * 4 * sizeof(unsigned char), _image, NULL);
        outputBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE,
                                            _width * _height * sizeof(unsigned char), NULL, NULL);

        prog = CreateProgramFromFile("kernels/grayscale.cl");
        CreateKernelFromProgram(prog, "grayscale_rgba");

        clSetKernelArg(GetKernel(0), 0, sizeof(cl_mem), (void *)&inputBuffer);
        clSetKernelArg(GetKernel(0), 1, sizeof(cl_mem), (void *)&outputBuffer);

        size_t global_work_size[1] = {_width * _height * 4 * sizeof(unsigned char)};
        clEnqueueNDRangeKernel(commandQueue, GetKernel(0), 1, NULL,
                            global_work_size, NULL, 0, NULL, NULL);

        clReleaseMemObject(inputBuffer);

        _imageIsGrayscaled = true;

        return 0;
    }

    void clone_image(unsigned char *dest) override
    {
        clEnqueueReadBuffer(commandQueue, outputBuffer, CL_TRUE, 0,
                    _width * _height * sizeof(unsigned char), dest, 0, NULL, NULL);
    }

    unsigned resize_image(unsigned scalingFactor) override
    {
        _width = _width / scalingFactor;
        _height = _height / scalingFactor;

        CreateKernelFromProgram(prog, "resize");

        status = clSetKernelArg(GetKernel(1), 0, sizeof(scalingFactor), &scalingFactor);
        status = clSetKernelArg(GetKernel(1), 1, sizeof(cl_mem), (void *)&outputBuffer);
        status = clSetKernelArg(GetKernel(1), 2, sizeof(cl_mem), (void *)&outputBuffer);

        size_t global_work_size[2];
        global_work_size[0] = _width * sizeof(unsigned char);
        global_work_size[1] = _height * sizeof(unsigned char);

        clEnqueueNDRangeKernel(commandQueue, GetKernel(1), 2, NULL,
                            global_work_size, NULL, 0, NULL, NULL);
        return (unsigned)status;
    }

    unsigned save_image(const char* filename) override
    {
        if(_imageIsGrayscaled)
        {
            _image = (unsigned char *)realloc(_image, _width * _height * sizeof(unsigned char));
            clone_image(_image);
            return LodepngWrapper::save_image(filename);
        }
        else
        {
            return LodepngWrapper::save_image(filename);
        }
    }

    int get_width()
    {
        return _width;
    }

    int get_height()
    {
        return _height;
    }

private:
    cl_mem outputBuffer;
    
    cl_program prog;
};

class OCL_Phase4 : public OCL_Base
{
public:
    OCL_Phase4()
    {
        img0.reset(new OCL_image());
    }

    ~OCL_Phase4()
    {
    }

    void Run() override
    {
    }

    std::unique_ptr<OCL_image> img0;
};

OCL_Phase4 ocl_phase4;

struct LoadImage : public IProgram
{
    int run() override
    {
        unsigned error = ocl_phase4.img0->load_image("../../source-img/im0.png");
        // error = img1.load_image("../../source-img/im1.png");
        return (int) error;
    }
};

struct ResizeImage : public IProgram
{
    int run() override
    {
        ocl_phase4.img0->resize_image(scaling_factor);
        return 0;
    }
};

struct TransformToGreyscale : public IProgram
{
    int run() override
    {
        ocl_phase4.img0->transform_to_grayscale();
        return 0;
    }
};

struct SaveGreyscaleImage : public IProgram
{
    int run() override
    {
        unsigned error = ocl_phase4.img0->save_image("../../output-img/im0_grey.png");
        // error = img1.save_image("../../output-img/im1_grey.png");
        return (int) error;
    }
};

struct SaveResizedImage : public IProgram
{
    int run() override
    {
        unsigned error = ocl_phase4.img0->save_image("../../output-img/im0_grey_resized.png");
        // error = img1.save_image("../../output-img/im1_grey_resized.png");
        return (int) error;
    }
};

// struct ZNCCResizedImage : public IProgram
// {
//     int run() override
//     {
//         unsigned char * t_img0 = (unsigned char*)malloc(img0.get_width() * img0.get_height());

//         unsigned char * t_img1 = (unsigned char*)malloc(img1.get_width() *
//                                                         img1.get_height());

//         img0.clone_image(t_img0);
//         img1.clone_image(t_img1);
        
//         unsigned char *t_leftToRightImage = (unsigned char*)malloc(img0.get_width() *
//                                                         img0.get_height());

//         unsigned char *t_rightToLeftImage = (unsigned char*)malloc(img0.get_width() *
//                                                         img0.get_height());

//         // run the ZNCC
//         OMP_ZNCCFilterOptimizedC(t_leftToRightImage, t_img0, t_img1, img0.get_width(), img0.get_height(), 9, 1);
//         OMP_ZNCCFilterOptimizedC(t_rightToLeftImage, t_img1, t_img0, img0.get_width(), img0.get_height(), 9, 2);

//         img0.set_image(t_leftToRightImage, img0.get_width(), img0.get_height(), GREY_CHANNELS);
//         img1.set_image(t_rightToLeftImage, img1.get_width(), img1.get_height(), GREY_CHANNELS);
        
//         img0.save_image("../../output-img/im0_grey_resized_zncc.png");
//         img1.save_image("../../output-img/im1_grey_resized_zncc.png");
        
//         free(t_img0);
//         free(t_img1);
//         free(t_leftToRightImage);
//         free(t_rightToLeftImage);

//         return 0;
//     }
// };

// struct CrosscheckImage : public IProgram
// {
//     int run() override
//     {
//         unsigned char * t_img0 = (unsigned char*)malloc(img0.get_width() * img0.get_height());
                                                        
//         unsigned char * t_img1 = (unsigned char*)malloc(img1.get_width() * img1.get_height());

//         unsigned char * t_combinedImg = (unsigned char*)malloc(img1.get_width() * img1.get_height());

//         img0.clone_image(t_img0);
//         img1.clone_image(t_img1);

//         crossCheckTwoImages(t_img0, t_img1, 50, t_combinedImg, img0.get_width() * img0.get_height());
//         combinedImage.set_image(t_combinedImg, img0.get_width(), img0.get_height(), GREY_CHANNELS);

//         unsigned error = combinedImage.save_image("../../output-img/im_cc.png");
//         free(t_img0);
//         free(t_img1);
//         free(t_combinedImg);

//         return (int) error;
//     }
// };

// struct OcclusionFilterImage : public IProgram
// {
//     int run() override
//     {
//         unsigned error = 0;

//         combinedImage.occlusion_fill(fillZeroPixels);
//         //img0.occlusion_fill(occFillOptimizedC);

//         error = combinedImage.save_image("../../output-img/im_of.png");
//         return (int) error;
//     }
// };


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
    // ZNCCResizedImage ZNCCResizedImage;
    // CrosscheckImage crosscheckImage;
    // OcclusionFilterImage occlusionFilterImage;


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

    // result = Program_sw.runProgram(ZNCCResizedImage);
    // std::cout << "ZNCC filter and save resized images return result: " << result << std::endl;
    // std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    // result = Program_sw.runProgram(crosscheckImage);
    // std::cout << "crosscheck and save resized image return result: " << result << std::endl;
    // std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    // result = Program_sw.runProgram(occlusionFilterImage);
    // std::cout << "Occlusion fill and save resized image return result: " << result << std::endl;
    // std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    sw.saveEndPoint();
    std::cout << "Total elapsed time: " << sw.getElapsedTime() << " us\n" << std::endl;

    printPlatformProfile(false);
    return 0;
}
