# Multiprocessor programming

Project goal is to implement Zero-mean Normalized Cross
Correlation (ZNCC) algorithm for calculating depth map for stereo images taking advantage of OpenCL and parallel computing.

## Status

----------

## Todo - C/C++

- Image resize?
- Normalization for depth map to range from 0 to 255.
  - Depth map contains values from 0 to *ndisp* and those needs to be normalized to range of grayscale pixel in image.
- Post processing
  - Cross-check
  - Occlusion filling

## Done - C/C++

- Grayscale conversion
- Applying a filter to image
- Profiling info
- Stopwatch
- Read image
- Write image

## Todo - OpenCL

- ?

## Done - OpenCL

- Some basic framework setup
- Grayscale conversion
