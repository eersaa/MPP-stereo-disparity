#ifndef OPENCL_BASE_H
#define OPENCL_BASE_H
#include <iostream>

#ifndef CL_TARGET_OPENCL_VERSION
#define CL_TARGET_OPENCL_VERSION 120
#endif
#include <CL/opencl.h>


class OCL_Base
{
public:
    OCL_Base();
    ~OCL_Base();

private:
    void init();

    cl_uint numPlatforms; //the NO. of platforms
	cl_platform_id platform = NULL; //the chosen platform
	cl_int status = 0;
    cl_platform_id* platforms;

    cl_uint numDevices = 0;
	cl_device_id *devices;

    cl_context context;
    cl_command_queue commandQueue;
};

    /* data */
#endif // OPENCL_BASE_H