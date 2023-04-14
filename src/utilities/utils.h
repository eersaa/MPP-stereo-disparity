#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

#ifndef CL_TARGET_OPENCL_VERSION
#define CL_TARGET_OPENCL_VERSION 120
#endif
#include <CL/opencl.h>


int printPlatformProfile(bool print_extras);

void movingAvgFilter(unsigned char* image, unsigned width, unsigned height, unsigned windowSize);
void ZNCCFilter(unsigned char* imageOut, unsigned char* image, unsigned char* image2, unsigned width, unsigned height, unsigned windowSize, unsigned leftToRight);
void ZNCCFilterOptimizedC(unsigned char* imageOut, unsigned char* image, unsigned char* image2, unsigned width, unsigned height, unsigned windowSize, unsigned leftToRight);

#endif  // UTIL_H