#include "phase1.h"

lodepng_wrapper::LodepngWrapper img0;

int matwidth = 100;
int matheight = 100;
int* matrixA;
int* matrixB;
int* matrixR;

/*
class OCL_Phase1
{
public:
    OCL_Phase1(std::unique_ptr<OCL_Base>& ocl_base)
        : _ocl_base(ocl_base)
    {
        _ocl_base.reset(new OCL_Base());
        
        init_programs();
        init_kernels();
    }

    ~OCL_Phase1()
    {
    }

    void init_programs()
    {
        program = _ocl_base->CreateProgramFromFile("kernels/p1-matrix-addition.cl");
    }

    void init_kernels()
    {
        _ocl_base->CreateKernelFromProgram(program, "matrix_addition");
    }

    unsigned matrix_addition()
    {
        int width = 100;
        int height = 100;

        cl_mem maInBuffer = clCreateBuffer(_ocl_base->context,
                                        CL_MEM_READ_WRITE,
                                        width * height * sizeof(int),
                                        NULL,
                                        NULL);

        cl_mem maOutBuffer = clCreateBuffer(_ocl_base->context,
                                        CL_MEM_READ_WRITE,
                                        width * height * sizeof(int),
                                        NULL,
                                        NULL);

        cl_int status;
        
        status = clSetKernelArg(_ocl_base->GetKernel(6), 0, sizeof(cl_mem), (void *)&maInBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(6), 1, sizeof(cl_mem), (void *)&maOutBuffer);

        size_t global_work_size[2];
        global_work_size[0] = width * sizeof(unsigned char);
        global_work_size[1] = height * sizeof(unsigned char);

        status = clEnqueueNDRangeKernel(_ocl_base->commandQueue,
                                        _ocl_base->GetKernel(6),
                                        2,
                                        NULL,
                                        global_work_size,
                                        NULL,
                                        0,
                                        NULL,
                                        NULL);

        return (unsigned)status;
    }

private:
    cl_program program;
    std::unique_ptr<OCL_Base>& _ocl_base;
};

OCL_Phase1 ocl_phase1;
*/

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

    struct CreateMatrices : public IProgram
    {
        int run() override
        {

            matrixA = (int*)malloc((matwidth * matheight) * sizeof(int));
            matrixB = (int*)malloc((matwidth * matheight) * sizeof(int));
            matrixR = (int*)malloc((matwidth * matheight) * sizeof(int));

            for (int i=0; i<matheight; i++) {
                for (int j=0; j<matwidth; j++) {
                    matrixA[i * matwidth + j] = i + 1;
                    matrixB[i * matwidth + j] = j + 2;
                }
            }

            for (int i=0; i<matheight; i++) {
                for (int j=0; j<matwidth; j++) {
                    matrixR[i * matwidth + j] = matrixA[i * matwidth + j] + matrixB[i * matwidth + j];
                }
            }

            unsigned error = 0;
            return (int) error;
        }
    };

    struct MatrixAdditionC : public IProgram
    {
        int run() override
        {

            int* matrixA = (int*)malloc((matwidth * matheight) * sizeof(int));
            int* matrixB = (int*)malloc((matwidth * matheight) * sizeof(int));
            matrixR = (int*)malloc((matwidth * matheight) * sizeof(int));

            for (int i=0; i<matheight; i++) {
                for (int j=0; j<matwidth; j++) {
                    matrixA[i * matwidth + j] = i + 1;
                    matrixB[i * matwidth + j] = j + 2;
                }
            }

            for (int i=0; i<matheight; i++) {
                for (int j=0; j<matwidth; j++) {
                    matrixR[i * matwidth + j] = matrixA[i * matwidth + j] + matrixB[i * matwidth + j];
                }
            }

            unsigned error = 0;
            return (int) error;
        }
    };

    struct MatrixAdditionOCL : public IProgram
    {
        int run() override
        {

            std::vector<std::string> example { "This", "is", "a", "test" };

            std::ofstream output_file("./example.txt");

            std::ostream_iterator<std::string> output_iterator(output_file, "\n");
            std::copy(std::begin(example), std::end(example), output_iterator);

            unsigned error = 0;
            return (int) error;
        }
    };

    struct SaveMatrixCpp : public IProgram
    {
        int run() override
        {

            FILE *f = fopen("../../output-img/p1-matAddCpp.txt", "w");
            if (f == NULL)
            {
                printf("Error opening file!\n");
                exit(1);
            }

            for (int i=0; i<matheight; i++) {
                for (int j=0; j<matwidth; j++) {
                    fprintf(f, "%d ", matrixR[i * matwidth + j]);
                }
                fprintf(f, "\n");
            }

            fclose(f);

            unsigned error = 0;
            return (int) error;
        }
    };

    struct SaveMatrixOCL : public IProgram
    {
        int run() override
        {

            FILE *fp = fopen("../../output-img/p1-matAddOcl.txt", "w");
            if (fp == NULL)
            {
                printf("Error opening file!\n");
                exit(1);
            }

            for (int i=0; i<matheight; i++) {
                for (int j=0; j<matwidth; j++) {
                    fprintf(fp, "%d ", matrixR[i * matwidth + j]);
                }
                fprintf(fp, "\n");
            }

            fclose(fp);

            unsigned error = 0;
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
    CreateMatrices createMatrices;
    MatrixAdditionC matrixAdditionC;
    MatrixAdditionOCL matrixAdditionOCL;
    SaveMatrixCpp saveMatrixCpp;
    SaveMatrixOCL saveMatrixOCL;

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

    result = Program_sw.runProgram(matrixAdditionC);
    std::cout << "C++ matrix creation and addition: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(saveMatrixCpp);
    std::cout << "C++ matrix save: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    // result = Program_sw.runProgram(cloneAndSaveImage);
    // std::cout << "Clone and save image return result: " << result << std::endl;
    // std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    sw.saveEndPoint();
    std::cout << "Total elapsed time: " << sw.getElapsedTime() << " us\n" << std::endl;

    free(matrixA);
    free(matrixB);
    free(matrixR);

    printPlatformProfile(false);
    return 0;
}
