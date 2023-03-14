#ifndef OPENCL_BASE_H
#define OPENCL_BASE_H
#include <iostream>
#include <string>
#include <fstream>

#ifndef CL_TARGET_OPENCL_VERSION
#define CL_TARGET_OPENCL_VERSION 120
#endif
#include <CL/opencl.h>


class OCL_Base
{
public:
    OCL_Base();
    ~OCL_Base();

    void CreateProgramFromFile(const char* filename);

protected:
    virtual void Run() = 0;

    cl_int status;

    cl_context context;
    cl_program program;
    cl_command_queue commandQueue;

private:
    void Init();

    cl_uint numPlatforms;
    cl_platform_id platform;
    cl_platform_id* platforms;

    cl_uint numDevices;
    cl_device_id *devices;


};

int convertToString(const char *filename, std::string& s);

    /* data */
#endif // OPENCL_BASE_H