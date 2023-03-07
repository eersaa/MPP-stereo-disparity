#include "util.h"
#include <iostream>
#include <vector>
#include <CL/cl.hpp>

extern int getPlatformProfile ()
{
    // Get the OpenCL platforms and devices
    // Include following information:
    // Platform count
    // Device count on platform
    // Device
    // Hardware version
    // Driver version
    // OpenCL C version
    // Parallel compute units
    // Max work item dimensions

    // Get the platforms
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    // Loop through the platforms
    for (auto& platform : platforms) {
        // Print platform info
        std::cout << "Platform name: " << platform.getInfo<CL_PLATFORM_NAME>() << "\n";
        std::cout << "Platform vendor: " << platform.getInfo<CL_PLATFORM_VENDOR>() << "\n";
        std::cout << "Platform version: " << platform.getInfo<CL_PLATFORM_VERSION>() << "\n";
        std::cout << "Platform extensions: " << platform.getInfo<CL_PLATFORM_EXTENSIONS>() << "\n";

        // Get the devices for this platform
        std::vector<cl::Device> devices;
        platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

        // Loop through the devices
        for (auto& device : devices) {
        // Print device info
        std::cout << "Device name: " << device.getInfo<CL_DEVICE_NAME>() << "\n";
        std::cout << "Device type: " << device.getInfo<CL_DEVICE_TYPE>() << "\n";
        std::cout << "Device max compute units: " << device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << "\n";
        std::cout << "Device max work group size: " << device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>() << "\n";
        std::cout << "Device max clock frequency: " << device.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>() << "\n";
        }
    }
    return 0;
}