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
        err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
        if (err != CL_SUCCESS || num_devices <= 0) {
            printf("Failed to find any OpenCL devices.\n");
            return -1;
        }

        std::cout << "Device count on platform " << i << ": " << num_devices << std::endl;

        // Get the device IDs
        cl_device_id devices[num_devices];
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);

        // Loop through the devices
        for (cl_uint j = 0; j < num_devices; j++) {
            // Print device info
            char device_name[100];
            char device_version[100];
            char driver_version[100];
            char opencl_c_version[100];
            cl_uint device_max_compute_units;
            cl_uint device_max_work_item_dimensions;
            cl_device_local_mem_type local_mem_type;
            cl_ulong local_mem_size; // in bytes
            cl_uint device_max_clock_frequency; // in MHz
            size_t device_max_work_group_size; // number of work-items
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, sizeof(device_name), device_name, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, sizeof(device_version), device_version, NULL);
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, sizeof(driver_version), driver_version, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, sizeof(opencl_c_version), opencl_c_version, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(device_max_compute_units), &device_max_compute_units, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(device_max_work_item_dimensions), &device_max_work_item_dimensions, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_LOCAL_MEM_SIZE, sizeof(local_mem_size), &local_mem_size, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(device_max_clock_frequency), &device_max_clock_frequency, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(device_max_work_group_size), &device_max_work_group_size, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_LOCAL_MEM_TYPE, sizeof(local_mem_type), &local_mem_type, NULL);
            size_t device_max_work_item_sizes[device_max_work_item_dimensions];
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(device_max_work_item_sizes), &device_max_work_item_sizes, NULL);
            printf("Device name: %s\n", device_name);
            printf("Hardware version: %s\n", device_version);
            printf("Driver version: %s\n", driver_version);
            printf("OpenCL C version: %s\n", opencl_c_version);
            printf("Parallel compute units: %u\n", device_max_compute_units);
            printf("Device max work item dimensions: %u\n", device_max_work_item_dimensions);
            if (local_mem_type == CL_LOCAL) {
                printf("Device local mem type: CL_LOCAL\n");
            }
            else if (local_mem_type == CL_GLOBAL) {
                printf("Device local mem type: CL_GLOBAL\n");
            }
            else {
                printf("Device local mem type: UNKNOWN\n");
            }
            printf("Device local mem size: %zu\n", local_mem_size);
            printf("Device max clock frequency: %u\n", device_max_clock_frequency);
            printf("Device max work group size: %zu\n", device_max_work_group_size);
            printf("Device max work item sizes: ");
            for (cl_uint k = 0; k < device_max_work_item_dimensions; k++) {
                if (k != device_max_work_item_dimensions - 1) {
                    printf("%zu, ", device_max_work_item_sizes[k]);
                }
                else {
                    printf("%zu", device_max_work_item_sizes[k]);
                }
            }
        }
    }
    return 0;
  }