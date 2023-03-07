#include "util.h"


int printPlatformProfile()
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


    // Get the number of platforms
    cl_uint num_platforms;
    cl_int err = clGetPlatformIDs(0, NULL, &num_platforms);
    if (err != CL_SUCCESS || num_platforms <= 0) {
        printf("Failed to find any OpenCL platforms.\n");
        return -1;
    }

    std::cout << "Platform count: " << num_platforms << std::endl;

    // Get the platform IDs
    cl_platform_id platforms[num_platforms];
    clGetPlatformIDs(num_platforms, platforms, NULL);

    // Loop through the platforms
    for (cl_uint i = 0; i < num_platforms; i++) {
        // Print platform info
        char platform_version[100];
        clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, sizeof(platform_version), platform_version, NULL);
        printf("Platform version: %s\n", platform_version);

        // Get the number of devices for this platform
        cl_uint num_devices;
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);

        std::cout << "Device count on platform " << i << ": " << num_devices << std::endl;

        // Get the device IDs
        cl_device_id devices[num_devices];
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);

        // Loop through the devices
        for (cl_uint j = 0; j < num_devices; j++) {
        // Print device info
        char device_name[100];
        cl_device_type device_type;
        cl_uint device_max_compute_units;
        size_t device_max_work_group_size;
        cl_uint device_max_clock_frequency;
        clGetDeviceInfo(devices[j], CL_DEVICE_NAME, sizeof(device_name), device_name, NULL);
        clGetDeviceInfo(devices[j], CL_DEVICE_TYPE, sizeof(device_type), &device_type, NULL);
        clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(device_max_compute_units), &device_max_compute_units, NULL);
        clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(device_max_work_group_size), &device_max_work_group_size, NULL);
        clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(device_max_clock_frequency), &device_max_clock_frequency, NULL);
        printf("Device name: %s\n", device_name);
        printf("Device type: %u\n", (unsigned)device_type);
        printf("Device max compute units: %u\n", device_max_compute_units);
        printf("Device max work group size: %zu\n", device_max_work_group_size);
        printf("Device max clock frequency: %u\n", device_max_clock_frequency);
        }
    }
    return 0;
  }