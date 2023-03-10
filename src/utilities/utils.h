#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifndef CL_TARGET_OPENCL_VERSION
#define CL_TARGET_OPENCL_VERSION 120
#endif
#include <CL/opencl.h>


int printPlatformProfile(bool print_extras);

void movingAvgFilter(unsigned char* image, int width, int height, int windowSize);

#endif  // UTIL_H