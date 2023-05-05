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
        if(imageBuffer != nullptr) clReleaseMemObject(imageBuffer);
        if(averageBuffer != nullptr) clReleaseMemObject(averageBuffer);
        if(stdDeviationBuffer != nullptr) clReleaseMemObject(stdDeviationBuffer);
    }

    unsigned transform_to_grayscale() override
    {
        cl_mem inputBuffer = clCreateBuffer(_ocl_base->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                            _width * _height * 4 * sizeof(unsigned char), _image, NULL);
        imageBuffer = clCreateBuffer(_ocl_base->context, CL_MEM_READ_WRITE,
                                            _width * _height * sizeof(unsigned char), NULL, NULL);

        clSetKernelArg(_ocl_base->GetKernel(0), 0, sizeof(cl_mem), (void *)&inputBuffer);
        clSetKernelArg(_ocl_base->GetKernel(0), 1, sizeof(cl_mem), (void *)&imageBuffer);

        size_t global_work_size[1] = {_width * _height * 4 * sizeof(unsigned char)};
        clEnqueueNDRangeKernel(_ocl_base->commandQueue, _ocl_base->GetKernel(0), 1, NULL,
                            global_work_size, NULL, 0, NULL, &_event);

        kernel_execution_times[0] = get_kernel_execution_time(_event, _ocl_base->commandQueue);

        clReleaseMemObject(inputBuffer);

        _imageIsGrayscaled = true;

        return 0;
    }

    void clone_image(unsigned char *dest) override
    {
        clEnqueueReadBuffer(_ocl_base->commandQueue, imageBuffer, CL_TRUE, 0,
                    _width * _height * sizeof(unsigned char), dest, 0, NULL, NULL);
    }

    unsigned resize_image(unsigned scalingFactor) override
    {
        _width = _width / scalingFactor;
        _height = _height / scalingFactor;

        cl_int status;
        status = clSetKernelArg(_ocl_base->GetKernel(1), 0, sizeof(scalingFactor), &scalingFactor);
        status = clSetKernelArg(_ocl_base->GetKernel(1), 1, sizeof(cl_mem), (void *)&imageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(1), 2, sizeof(cl_mem), (void *)&imageBuffer);

        size_t global_work_size[2];
        global_work_size[0] = _width * sizeof(unsigned char);
        global_work_size[1] = _height * sizeof(unsigned char);

        clEnqueueNDRangeKernel(_ocl_base->commandQueue, _ocl_base->GetKernel(1), 2, NULL,
                            global_work_size, NULL, 0, NULL, &_event);

        kernel_execution_times[1] = get_kernel_execution_time(_event, _ocl_base->commandQueue);

        return (unsigned)status;
    }

    unsigned average(int windowSize)
    {
        averageBuffer = clCreateBuffer(_ocl_base->context,
                                        CL_MEM_READ_WRITE,
                                        _width * _height * sizeof(float),
                                        NULL,
                                        NULL);

        cl_int status;
        status = clSetKernelArg(_ocl_base->GetKernel(2), 0, sizeof(cl_mem), (void *)&imageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(2), 1, sizeof(cl_mem), (void *)&averageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(2), 2, sizeof(int), &windowSize);

        size_t global_work_size[2];
        global_work_size[0] = _width * sizeof(unsigned char);
        global_work_size[1] = _height * sizeof(unsigned char);

        status = clEnqueueNDRangeKernel(_ocl_base->commandQueue,
                                        _ocl_base->GetKernel(2),
                                        2,
                                        NULL,
                                        global_work_size,
                                        NULL,
                                        0,
                                        NULL,
                                        &_event);

        kernel_execution_times[2] = get_kernel_execution_time(_event, _ocl_base->commandQueue);

        return (unsigned)status;
    }

    unsigned standard_deviation(int windowSize)
    {
        stdDeviationBuffer = clCreateBuffer(_ocl_base->context,
                                        CL_MEM_READ_WRITE,
                                        _width * _height * sizeof(float),
                                        NULL,
                                        NULL);

        cl_int status;
        status = clSetKernelArg(_ocl_base->GetKernel(3), 0, sizeof(cl_mem), (void *)&imageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(3), 1, sizeof(cl_mem), (void *)&stdDeviationBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(3), 2, sizeof(cl_mem), (void *)&averageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(3), 3, sizeof(int), &windowSize);

        size_t global_work_size[2];
        global_work_size[0] = _width * sizeof(unsigned char);
        global_work_size[1] = _height * sizeof(unsigned char);

        status = clEnqueueNDRangeKernel(_ocl_base->commandQueue,
                                        _ocl_base->GetKernel(3),
                                        2,
                                        NULL,
                                        global_work_size,
                                        NULL,
                                        0,
                                        NULL,
                                        &_event);

        kernel_execution_times[3] = get_kernel_execution_time(_event, _ocl_base->commandQueue);

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

    void print_kernel_execution_times()
    {
        std::cout << "Grayscale kernel execution time: " << kernel_execution_times[0] << " us\n";
        std::cout << "Resize kernel execution time: " << kernel_execution_times[1] << " us\n";
        std::cout << "Average kernel execution time: " << kernel_execution_times[2] << " us\n";
        std::cout << "Standard deviation kernel execution time: " << kernel_execution_times[3] << " us\n";

        std::cout << "Total kernel execution time: " << kernel_execution_times[0] 
                                                        + kernel_execution_times[1] 
                                                        + kernel_execution_times[2] 
                                                        + kernel_execution_times[3] << " us\n" << std::endl;
    }


    cl_mem imageBuffer = nullptr;
    cl_mem averageBuffer = nullptr;
    cl_mem stdDeviationBuffer = nullptr;
private:
    
    std::unique_ptr<OCL_Base>& _ocl_base;

    cl_event _event;

    // 0 - grayscale
    // 1 - resize
    // 2 - average
    // 3 - standard deviation
    unsigned long kernel_execution_times[4] = {0, 0, 0, 0};
};

class OCL_Phase4
{
public:
    OCL_Phase4()
    {
        _ocl_base.reset(new OCL_Base());
        img0.reset(new OCL_image(_ocl_base));
        img1.reset(new OCL_image(_ocl_base));
        
        init_programs();
        init_kernels();
    }

    ~OCL_Phase4()
    {
    }

    void init_programs()
    {
        prog = _ocl_base->CreateProgramFromFile("kernels/grayscale.cl");
        prog_average = _ocl_base->CreateProgramFromFile("kernels/p4-average.cl");
        prog_stdDeviation = _ocl_base->CreateProgramFromFile("kernels/p4-standard-deviation.cl");
        prog_ZNCC = _ocl_base->CreateProgramFromFile("kernels/p4-zncc-max.cl");
        prog_cc = _ocl_base->CreateProgramFromFile("kernels/p4-cc.cl");
        prog_of = _ocl_base->CreateProgramFromFile("kernels/p4-of.cl");
        prog_ma = _ocl_base->CreateProgramFromFile("kernels/p1-ma.cl");
    }

    void init_kernels()
    {
        _ocl_base->CreateKernelFromProgram(prog, "grayscale_rgba");
        _ocl_base->CreateKernelFromProgram(prog, "resize");
        _ocl_base->CreateKernelFromProgram(prog_average, "average");
        _ocl_base->CreateKernelFromProgram(prog_stdDeviation, "standardDeviation");
        _ocl_base->CreateKernelFromProgram(prog_ZNCC, "znccMax");
        _ocl_base->CreateKernelFromProgram(prog_cc, "cross_check");
        _ocl_base->CreateKernelFromProgram(prog_of, "occlusion_fill");
        _ocl_base->CreateKernelFromProgram(prog_ma, "matrix_addition");
    }

    unsigned ZNCC(int windowSize, int maxDisparity)
    {
        img0->average(windowSize);
        img1->average(windowSize);
        img0->standard_deviation(windowSize);
        img1->standard_deviation(windowSize);

        int width = img0->get_width();
        int height = img0->get_height();

        cl_mem znccBuffer = clCreateBuffer(_ocl_base->context,
                                        CL_MEM_READ_WRITE,
                                        width * height * sizeof(unsigned char),
                                        NULL,
                                        NULL);

        int leftToRight = 1;
        cl_int status;
        status = clSetKernelArg(_ocl_base->GetKernel(4), 0, sizeof(cl_mem), (void *)&img0->imageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 1, sizeof(cl_mem), (void *)&img1->imageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 2, sizeof(cl_mem), (void *)&img0->averageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 3, sizeof(cl_mem), (void *)&img1->averageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 4, sizeof(cl_mem), (void *)&img0->stdDeviationBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 5, sizeof(cl_mem), (void *)&img1->stdDeviationBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 6, sizeof(cl_mem), (void *)&znccBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 7, sizeof(int), &windowSize);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 8, sizeof(int), &leftToRight);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 9, sizeof(int), &maxDisparity);

        size_t global_work_size[2];
        global_work_size[0] = width * sizeof(unsigned char);
        global_work_size[1] = height * sizeof(unsigned char);

        status = clEnqueueNDRangeKernel(_ocl_base->commandQueue,
                                        _ocl_base->GetKernel(4),
                                        2,
                                        NULL,
                                        global_work_size,
                                        NULL,
                                        0,
                                        NULL,
                                        &_event);

        kernel_execution_times[0] = get_kernel_execution_time(_event, _ocl_base->commandQueue);

        cl_mem znccBuffer2 = clCreateBuffer(_ocl_base->context,
                                        CL_MEM_READ_WRITE,
                                        width * height * sizeof(unsigned char),
                                        NULL,
                                        NULL);

        leftToRight = 2;
        status = clSetKernelArg(_ocl_base->GetKernel(4), 0, sizeof(cl_mem), (void *)&img1->imageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 1, sizeof(cl_mem), (void *)&img0->imageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 2, sizeof(cl_mem), (void *)&img1->averageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 3, sizeof(cl_mem), (void *)&img0->averageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 4, sizeof(cl_mem), (void *)&img1->stdDeviationBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 5, sizeof(cl_mem), (void *)&img0->stdDeviationBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 6, sizeof(cl_mem), (void *)&znccBuffer2);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 7, sizeof(int), &windowSize);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 8, sizeof(int), &leftToRight);
        status = clSetKernelArg(_ocl_base->GetKernel(4), 9, sizeof(int), &maxDisparity);

        size_t global_work_size2[2];
        global_work_size2[0] = width * sizeof(unsigned char);
        global_work_size2[1] = height * sizeof(unsigned char);

        status = clEnqueueNDRangeKernel(_ocl_base->commandQueue,
                                        _ocl_base->GetKernel(4),
                                        2,
                                        NULL,
                                        global_work_size2,
                                        NULL,
                                        0,
                                        NULL,
                                        &_event);

        kernel_execution_times[1] = get_kernel_execution_time(_event, _ocl_base->commandQueue);
        
        status = clEnqueueCopyBuffer(_ocl_base->commandQueue,
                                    znccBuffer,
                                    img0->imageBuffer,
                                    0,
                                    0,
                                    width * height * sizeof(unsigned char),
                                    0,
                                    NULL,
                                    NULL);

        status = clEnqueueCopyBuffer(_ocl_base->commandQueue,
                                    znccBuffer2,
                                    img1->imageBuffer,
                                    0,
                                    0,
                                    width * height * sizeof(unsigned char),
                                    0,
                                    NULL,
                                    NULL);

        return (unsigned)status;
    }

    unsigned crossCheck_Images(int threshold)
    {
        int width = img0->get_width();
        int height = img0->get_height();

        cl_mem ccBuffer = clCreateBuffer(_ocl_base->context,
                                        CL_MEM_READ_WRITE,
                                        width * height * sizeof(unsigned char),
                                        NULL,
                                        NULL);

        cl_int status;
        status = clSetKernelArg(_ocl_base->GetKernel(5), 0, sizeof(cl_mem), (void *)&img0->imageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(5), 1, sizeof(cl_mem), (void *)&img1->imageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(5), 2, sizeof(int), &threshold);
        status = clSetKernelArg(_ocl_base->GetKernel(5), 3, sizeof(cl_mem), (void *)&ccBuffer);

        size_t global_work_size[2];
        global_work_size[0] = width * sizeof(unsigned char);
        global_work_size[1] = height * sizeof(unsigned char);

        status = clEnqueueNDRangeKernel(_ocl_base->commandQueue,
                                        _ocl_base->GetKernel(5),
                                        2,
                                        NULL,
                                        global_work_size,
                                        NULL,
                                        0,
                                        NULL,
                                        &_event);

        kernel_execution_times[2] = get_kernel_execution_time(_event, _ocl_base->commandQueue);

        status = clEnqueueCopyBuffer(_ocl_base->commandQueue,
                                    ccBuffer,
                                    img0->imageBuffer,
                                    0,
                                    0,
                                    width * height * sizeof(unsigned char),
                                    0,
                                    NULL,
                                    NULL);

        return (unsigned)status;
    }

    unsigned occlusion_fill_image()
    {
        int width = img0->get_width();
        int height = img0->get_height();

        cl_mem ofBuffer = clCreateBuffer(_ocl_base->context,
                                        CL_MEM_READ_WRITE,
                                        width * height * sizeof(unsigned char),
                                        NULL,
                                        NULL);

        cl_int status;
        status = clSetKernelArg(_ocl_base->GetKernel(6), 0, sizeof(cl_mem), (void *)&img0->imageBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(6), 1, sizeof(cl_mem), (void *)&ofBuffer);

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
                                        &_event);

        kernel_execution_times[3] = get_kernel_execution_time(_event, _ocl_base->commandQueue);

        status = clEnqueueCopyBuffer(_ocl_base->commandQueue,
                                    ofBuffer,
                                    img0->imageBuffer,
                                    0,
                                    0,
                                    width * height * sizeof(unsigned char),
                                    0,
                                    NULL,
                                    NULL);

        return (unsigned)status;
    }

    unsigned matrix_addition()
    {

        cl_mem aBuffer = clCreateBuffer(_ocl_base->context,
                                        CL_MEM_READ_WRITE,
                                        matwidth * matheight * sizeof(int),
                                        NULL,
                                        NULL);

        cl_mem bBuffer = clCreateBuffer(_ocl_base->context,
                                        CL_MEM_READ_WRITE,
                                        matwidth * matheight * sizeof(int),
                                        NULL,
                                        NULL);

        cl_mem rBuffer = clCreateBuffer(_ocl_base->context,
                                        CL_MEM_READ_WRITE,
                                        matwidth * matheight * sizeof(int),
                                        NULL,
                                        NULL);

        cl_int status;

        status = clEnqueueWriteBuffer(_ocl_base->commandQueue,
                                        aBuffer,
                                        CL_TRUE,
                                        0,
                                        matwidth * matheight * sizeof(int),
                                        matrixA,
                                        0,
                                        NULL,
                                        NULL);

        status = clEnqueueWriteBuffer(_ocl_base->commandQueue,
                                        bBuffer,
                                        CL_TRUE,
                                        0,
                                        matwidth * matheight * sizeof(int),
                                        matrixB,
                                        0,
                                        NULL,
                                        NULL);

        status = clSetKernelArg(_ocl_base->GetKernel(7), 0, sizeof(cl_mem), (void *)&aBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(7), 1, sizeof(cl_mem), (void *)&bBuffer);
        status = clSetKernelArg(_ocl_base->GetKernel(7), 2, sizeof(cl_mem), (void *)&rBuffer);

        size_t global_work_size[2];
        global_work_size[0] = matwidth * sizeof(int);
        global_work_size[1] = matheight * sizeof(int);

        status = clEnqueueNDRangeKernel(_ocl_base->commandQueue,
                                        _ocl_base->GetKernel(7),
                                        2,
                                        NULL,
                                        global_work_size,
                                        NULL,
                                        0,
                                        NULL,
                                        &_event);

        kernel_execution_times[4] = get_kernel_execution_time(_event, _ocl_base->commandQueue);

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
        std::cout << "Matrix addition: " << kernel_execution_times[4] << " us\n\n";
    }

    std::unique_ptr<OCL_image> img0;
    std::unique_ptr<OCL_image> img1;

    std::unique_ptr<OCL_Base> _ocl_base;

private:
    cl_program prog;
    cl_program prog_average;
    cl_program prog_stdDeviation;
    cl_program prog_ZNCC;
    cl_program prog_cc;
    cl_program prog_of;
    cl_program prog_ma;

    cl_event _event;

    // 0 - ZNCC image0
    // 1 - ZNCC image1
    // 2 - cross check
    // 3 - occlusion fill
    unsigned long kernel_execution_times[5] = {0, 0, 0, 0, 0};
};

OCL_Phase4 ocl_phase4;

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
