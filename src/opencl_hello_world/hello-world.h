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

class OCL_HelloWorld : public OCL_Base
{
public:
    OCL_HelloWorld();
    ~OCL_HelloWorld();

private:

};

#endif // HELLO_WORLD_H