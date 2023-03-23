#include "opencl_base.h"

OCL_Base::OCL_Base()
{
    platform = NULL;
    status = 0;

    numDevices = 0;

    Init();
}

OCL_Base::~OCL_Base()
{
    status = clReleaseCommandQueue(commandQueue); //Release  Command queue.
    status = clReleaseContext(context); //Release context.

    if (devices != NULL)
    {
        free(devices);
        devices = NULL;
    }
}

void OCL_Base::CreateProgramFromFile(const char* filename)
{
    /*Step 5: Create program object */
    std::string sourceStr;
    status = convertToString(filename, sourceStr);
    const char *source = sourceStr.c_str();
    size_t sourceSize[] = { strlen(source) };
    program = clCreateProgramWithSource(context, 1, &source, sourceSize, NULL);

    /*Step 6: Build program. */
    status = clBuildProgram(program, 1, devices, NULL, NULL, NULL);
}

void OCL_Base::Init()
{
    /*Step1: Getting platforms and choose an available one.*/
    status = clGetPlatformIDs(0, NULL, &numPlatforms);
    if (status != CL_SUCCESS)
    {
        std::cout << "Error: Getting platforms!" << std::endl;
    }

    /*For clarity, choose the first available platform. */
    if (numPlatforms > 0)
    {
        platforms = (cl_platform_id*)malloc(numPlatforms * sizeof(cl_platform_id));
        status = clGetPlatformIDs(numPlatforms, platforms, NULL);
        platform = platforms[0];
        free(platforms);
    }

    /*Step 2:Query the platform and choose the first GPU device if has one.Otherwise use the CPU as device.*/
    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
    if (numDevices == 0) //no GPU available.
    {
        std::cout << "No GPU device available." << std::endl;
        std::cout << "Choose CPU as default device." << std::endl;
        status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 0, NULL, &numDevices);
        devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
        status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, numDevices, devices, NULL);
    }
    else
    {
        devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
        status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, numDevices, devices, NULL);
    }

    /*Step 3: Create context.*/
    context = clCreateContext(NULL, 1, devices, NULL, NULL, NULL);

    /*Step 4: Creating command queue associate with the context.*/
    commandQueue = clCreateCommandQueue(context, devices[0], 0, NULL);

}

/* convert the kernel file into a string */
int convertToString(const char *filename, std::string& s)
{
    size_t size;
    char*  str;
    std::fstream f(filename, (std::fstream::in | std::fstream::binary));

    if (f.is_open())
    {
        size_t fileSize;
        f.seekg(0, std::fstream::end);
        size = fileSize = (size_t)f.tellg();
        f.seekg(0, std::fstream::beg);
        str = new char[size + 1];
        if (!str)
        {
            f.close();
            return 0;
        }

        f.read(str, fileSize);
        f.close();
        str[size] = '\0';
        s = str;
        delete[] str;
        return 0;
    }
    std::cout << "Error: failed to open file\n:" << filename << std::endl;
    return 1;
}