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

bool differenceIsOverThreshold(int pixel1, int pixel2, int threshold);

int crossCheck(int pixel1, int pixel2, int threshold);


#endif  // UTIL_H