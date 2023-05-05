#include "phase1.h"

lodepng_wrapper::LodepngWrapper img0;

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

    struct MatrixAdditionC : public IProgram
    {
        int run() override
        {

            int matSize = 100;
            float **matrixA;
            float **matrixB;
            float **matrixR;

            // Allocate memory for each vector on host
            matrixA = (float**)malloc(matSize * sizeof(float*));
            matrixB = (float**)malloc(matSize * sizeof(float*));
            matrixR = (float**)malloc(matSize * sizeof(float*));

            int i = 0;
            int j = 0;
            float sum = 0;

            for (i = 0; i < matSize; i++) {
                matrixA[i] = (float *)malloc(matSize * sizeof(float*));
            }   

            for (i = 0; i < matSize; i++){
                matrixB[i] = (float *)malloc(matSize * sizeof(float*));
            }

            for (i = 0; i < matSize; i++){
                matrixR[i] = (float *)malloc(matSize * sizeof(float*));
            }
            

            //fill matrices
            for (i=0; i<matSize; i++) {
                for (j=0; j<matSize; j++) {
                    matrixA[i][j] = i + 1;
                    matrixB[i][j] = j + 2;
                }
            }
            
            float sum = 0;

            //calculate result matrix
            for (int i=0; i<matSize; i++) {
                for (int j=0; j<matSize; j++) {
                    matrixR[i][j] = matrixA[i][j] + matrixB[i][j];
                }
            }

            std::ofstream output_file("../../output-img/example.txt");

            std::vector<std::vector<int> > vec {
            {1, 2, 3, 4},
            {4, 5, 6, 5}};

            for(const auto& row : vec) {
                std::copy(row.cbegin(), row.cend(), std::ostream_iterator<float>(output_file, " "));
            output_file << '\n';
            }

            free(matrixA);
            free(matrixB);
            free(matrixR);

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
    MatrixAdditionC matrixAdditionC;
    MatrixAdditionOCL matrixAdditionOCL;

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
    std::cout << "C++ matrix addition: " << result << std::endl;
    std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    // result = Program_sw.runProgram(cloneAndSaveImage);
    // std::cout << "Clone and save image return result: " << result << std::endl;
    // std::cout << "Elapsed time: " << Program_sw.getElapsedTime() << " us" << std::endl;

    sw.saveEndPoint();
    std::cout << "Total elapsed time: " << sw.getElapsedTime() << " us\n" << std::endl;

    printPlatformProfile(false);
    return 0;
}
