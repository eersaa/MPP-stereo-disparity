#include "phase1.h"

lodepng_wrapper::LodepngWrapper img0;

int matwidth = 100;
int matheight = 100;
int* matrixA;
int* matrixB;
int* matrixRcpp;
int* matrixRocl;

// Get kernel execution time in microseconds
unsigned long get_kernel_execution_time(cl_event &event, cl_command_queue &command_queue)
{
    clFinish(command_queue);

    cl_ulong time_start;
    cl_ulong time_end;

    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);

    return (time_end - time_start) / 1000;
}

class OCL_image : public lodepng_wrapper::LodepngWrapper
{
public:
    OCL_image(std::unique_ptr<OCL_Base>& ocl_base)
        : _ocl_base(ocl_base)
    {
    }

    ~OCL_image()
    {
    }

private:
    
    std::unique_ptr<OCL_Base>& _ocl_base;

    cl_event _event;

};

class OCL_Phase4
{
public:
    OCL_Phase4()
    {
        _ocl_base.reset(new OCL_Base());
        
        init_programs();
        init_kernels();
    }

    ~OCL_Phase4()
    {
    }

    void init_programs()
    {
        prog_ma = _ocl_base->CreateProgramFromFile("kernels/p1-ma.cl");
    }

    void init_kernels()
    {
        _ocl_base->CreateKernelFromProgram(prog_ma, "matrix_addition");
    }

    unsigned matrix_addition()
    {
        //Creating OpenCL buffers for matrices
        cl_mem aBuffer = clCreateBuffer(_ocl_base->context,
                                        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        matwidth * matheight * sizeof(int),
                                        matrixA,
                                        NULL);

        cl_mem bBuffer = clCreateBuffer(_ocl_base->context,
                                        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        matwidth * matheight * sizeof(int),
                                        matrixB,
                                        NULL);

        cl_mem rBuffer = clCreateBuffer(_ocl_base->context,
                                        CL_MEM_READ_WRITE,
                                        matwidth * matheight * sizeof(int),
                                        NULL,
                                        NULL);

        cl_int status;

        //Setting buffers to kernel arguments
        status = clSetKernelArg(_ocl_base->GetKernel(0), 0, sizeof(cl_mem), (void *)&aBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(0), 1, sizeof(cl_mem), (void *)&bBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(0), 2, sizeof(cl_mem), (void *)&rBuffer);

        size_t global_work_size[2];
        global_work_size[0] = matwidth * sizeof(int);
        global_work_size[1] = matheight * sizeof(int);

        //Enqueueing kernel
        status = clEnqueueNDRangeKernel(_ocl_base->commandQueue,
                                        _ocl_base->GetKernel(0),
                                        2,
                                        NULL,
                                        global_work_size,
                                        NULL,
                                        0,
                                        NULL,
                                        &_event);

        kernel_execution_times[0] = get_kernel_execution_time(_event, _ocl_base->commandQueue);

        //Reading result from GPU memory to main memory
        status = clEnqueueReadBuffer(_ocl_base->commandQueue,
                            rBuffer,
                            0,
                            0,
                            matwidth * matheight * sizeof(int),
                            matrixRocl,
                            0,
                            NULL,
                            NULL);

        return (unsigned)status;
    }

    void print_kernel_execution_times()
    {
        std::cout << "OpenCL kernel execution times\n";
        std::cout << "Matrix addition: " << kernel_execution_times[0] << " us\n\n";
    }

    std::unique_ptr<OCL_Base> _ocl_base;

private:
    cl_program prog_ma;

    cl_event _event;

    // 0 - Matrix addition
    unsigned long kernel_execution_times[5] = {0, 0, 0, 0, 0};
};

OCL_Phase4 ocl_phase4;

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
            matrixRcpp = (int*)malloc((matwidth * matheight) * sizeof(int));
            matrixRocl = (int*)malloc((matwidth * matheight) * sizeof(int));

            for (int i=0; i<matheight; i++) {
                for (int j=0; j<matwidth; j++) {
                    matrixA[i * matwidth + j] = i + 1;
                    matrixB[i * matwidth + j] = j + 2;
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

            for (int i=0; i<matheight; i++) {
                for (int j=0; j<matwidth; j++) {
                    matrixRcpp[i * matwidth + j] = matrixA[i * matwidth + j] + matrixB[i * matwidth + j];
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
            ocl_phase4.matrix_addition();

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
                    fprintf(f, "%d ", matrixRcpp[i * matwidth + j]);
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
                    fprintf(fp, "%d ", matrixRocl[i * matwidth + j]);
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

    result = Program_sw.runProgram(createMatrices);
    std::cout << "matrix creation: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(matrixAdditionC);
    std::cout << "C++ matrix addition: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(matrixAdditionOCL);
    std::cout << "OpenCL matrix addition: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(saveMatrixOCL);
    std::cout << "OpenCL matrix save: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    result = Program_sw.runProgram(saveMatrixCpp);
    std::cout << "C++ matrix save: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    sw.saveEndPoint();
    std::cout << "Total elapsed time: " << sw.getElapsedTime() << " us\n" << std::endl;

    ocl_phase4.print_kernel_execution_times();

    free(matrixA);
    free(matrixB);
    free(matrixRcpp);
    free(matrixRocl);

    printPlatformProfile(false);
    return 0;
}
