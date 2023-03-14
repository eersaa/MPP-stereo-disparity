#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#ifndef CL_TARGET_OPENCL_VERSION
#define CL_TARGET_OPENCL_VERSION 120
#endif
#include <CL/opencl.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

#include "opencl_base.h"

class OCL_HelloWorld : public OCL_Base
{
public:
    OCL_HelloWorld();
    ~OCL_HelloWorld();

    void Run() override;
private:

    cl_kernel kernel;
    cl_mem inputBuffer;
    cl_mem outputBuffer;

    const char* input;
    char* output;

    int inputSize;
    int outputSize;

};

#endif // HELLO_WORLD_H