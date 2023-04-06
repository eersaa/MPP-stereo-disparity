#include "utils.h"
#include <math.h>


int printPlatformProfile(bool print_extras)
{
    // Get the number of platforms
    cl_uint num_platforms;
    cl_int err = clGetPlatformIDs(0, NULL, &num_platforms);
    if (err != CL_SUCCESS || num_platforms <= 0) {
        std::cout << "Failed to find any OpenCL platforms." << std::endl;
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
        std::cout << "Platform version: " << platform_version << std::endl;

        // Get the number of devices for this platform
        cl_uint num_devices;
        err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
        if (err != CL_SUCCESS || num_devices <= 0) {
            std::cout << "Failed to find any OpenCL devices." << std::endl;
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
            cl_uint device_max_compute_units; // number of parallel compute units
            cl_uint device_max_work_item_dimensions; // number of dimensions
            cl_device_local_mem_type local_mem_type; // CL_LOCAL or CL_GLOBAL
            cl_ulong local_mem_size; // in bytes
            cl_uint device_max_clock_frequency; // in MHz
            cl_ulong device_max_constant_buffer_size; // in bytes
            size_t device_max_work_group_size; // number of work-items
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, sizeof(device_name), device_name, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, sizeof(device_version), device_version, NULL);
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, sizeof(driver_version), driver_version, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, sizeof(opencl_c_version), opencl_c_version, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(device_max_compute_units), &device_max_compute_units, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(device_max_work_item_dimensions), &device_max_work_item_dimensions, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_LOCAL_MEM_SIZE, sizeof(local_mem_size), &local_mem_size, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(device_max_clock_frequency), &device_max_clock_frequency, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(device_max_constant_buffer_size), &device_max_constant_buffer_size, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(device_max_work_group_size), &device_max_work_group_size, NULL);
            clGetDeviceInfo(devices[j], CL_DEVICE_LOCAL_MEM_TYPE, sizeof(local_mem_type), &local_mem_type, NULL);
            size_t device_max_work_item_sizes[device_max_work_item_dimensions];
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(device_max_work_item_sizes), &device_max_work_item_sizes, NULL);
            std::cout << "Device name: " << device_name << std::endl;
            std::cout << "Hardware version: " << device_version << std::endl;
            std::cout << "Driver version: " << driver_version << std::endl;
            std::cout << "OpenCL C version: " << opencl_c_version << std::endl;
            std::cout << "Parallel compute units: " << device_max_compute_units << std::endl;
            std::cout << "Device max work item dimensions: " << device_max_work_item_dimensions << std::endl;

            if (print_extras) {
                if (local_mem_type == CL_LOCAL) {
                    std::cout << "Device local mem type: CL_LOCAL" << std::endl;
                }
                else if (local_mem_type == CL_GLOBAL) {
                    std::cout << "Device local mem type: CL_GLOBAL" << std::endl;
                }
                else {
                    std::cout << "Device local mem type: UNKNOWN" << std::endl;
                }
                std::cout << "Device local mem size: " << local_mem_size << std::endl;
                std::cout << "Device max clock frequency: " << device_max_clock_frequency << std::endl;
                std::cout << "Device max constant buffer size: " << device_max_constant_buffer_size << std::endl;
                std::cout << "Device max work group size: " << device_max_work_group_size << std::endl;
                std::cout << "Device max work item sizes: ";
                for (cl_uint k = 0; k < device_max_work_item_dimensions; k++) {
                    std::cout << device_max_work_item_sizes[k];
                    if (k < device_max_work_item_dimensions - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
            }
        }
    }
    return 0;
  }


void movingAvgFilter(unsigned char* image, unsigned width, unsigned height, unsigned windowSize) {
  unsigned char* imageCopy = (unsigned char*)malloc(sizeof(unsigned char) * width * height);
  int windowSizeHalf = windowSize / 2;

  // Loop through the image
  for (unsigned y = 0; y < height; y++) {
    for (unsigned x = 0; x < width; x++) {
      int sum = 0;
      int count = 0;

      // Loop through the window
      for (int i = -windowSizeHalf; i <= windowSizeHalf; i++) {
        for (int j = -windowSizeHalf; j <= windowSizeHalf; j++) {
          int x2 = x + j;
          int y2 = y + i;

          // Check that the pixel is inside the image
          if (x2 >= 0 && x2 < (int)width && y2 >= 0 && y2 < (int)height) {
            sum += image[y2 * width + x2];
            count++;
          }
        }
      }

      // Set the pixel value
      imageCopy[y * width + x] = sum / count;
    }
  }

  // Copy the image back
  memcpy(image, imageCopy, sizeof(unsigned char) * width * height);

  // Free the memory
  free(imageCopy);
}

void ZNCCFilter(unsigned char* imageOut, unsigned char* image, unsigned char* image2, unsigned width, unsigned height, unsigned windowSize, unsigned leftToRight) {
  unsigned char* imageCopy = (unsigned char*)malloc(sizeof(unsigned char) * width * height);
  int windowSizeHalf = windowSize / 2;

  //int leftToRight = 1;

  float zncc = 0;
  int minDisp = 0;
  int maxDisp = 8;
  int dispRange = maxDisp - minDisp;
  int d = 0;
  int x2r = 0;

  // Loop through the image
  for (unsigned y = 0; y < height; y++) {
    for (unsigned x = 0; x < width; x++) {
      float sum = 0;
      float sum2 = 0;
      int count = 0;

      zncc = 0;

      for (d = minDisp; d < maxDisp; d++) {

        

        sum = 0;
        sum2 = 0;

        count = 0;

        // Loop through the window to get the average value
        for (int i = -windowSizeHalf; i <= windowSizeHalf; i++) {
          for (int j = -windowSizeHalf; j <= windowSizeHalf; j++) {
            int x2 = x + j;
            int y2 = y + i;

            if (leftToRight == 1) {
              x2r = x2 - d;
            }
            else {
              x2r = x2 + d;
            }

            // Check that the pixel is inside the image
            if (x2 >= 0 && x2 < (int)width && x2r >= 0 && x2r < (int)width && y2 >= 0 && y2 < (int)height) {
              sum += image[y2 * width + x2];
              sum2 += image2[y2 * width + x2r];

              count++;
            }
          }
        }

        if (count == 0) {
          count = 1;
        }

        float avg = sum / count;
        float avg2 = sum2 / count;

        //float mean_l = avg;
        //float mean_r = avg2;

        count = 0;
        sum = 0;
        sum2 = 0;
        
        // Loop through the window to get the standard deviation
        for (int i = -windowSizeHalf; i <= windowSizeHalf; i++) {
          for (int j = -windowSizeHalf; j <= windowSizeHalf; j++) {
            int x2 = x + j;
            int y2 = y + i;

            if (leftToRight == 1) {
              x2r = x2 - d;
            }
            else {
              x2r = x2 + d;
            }

            // Check that the pixel is inside the image
            if (x2 >= 0 && x2 < (int)width && x2r >= 0 && x2r < (int)width && y2 >= 0 && y2 < (int)height) {
              sum += pow((image[y2 * width + x2] - avg), 2);
              sum2 += pow((image2[y2 * width + x2r] - avg2), 2);


              count++;
            }
          }
        }
        float std = pow(sum, 0.5);
        float std2 = pow(sum2, 0.5);
        //float std_r = std2;

        //float std = sum / count;
        //float std2 = sum2 / count;

        

        count = 0;
        sum = 0;


        //float pixel_left = 0;
        //float pixel_right = 0;
        //float N = 0;

      
        // Loop through the window to get the ZNCC value
        for (int i = -windowSizeHalf; i <= windowSizeHalf; i++) {
          for (int j = -windowSizeHalf; j <= windowSizeHalf; j++) {
            int x2 = x + j;
            int y2 = y + i;

            if (leftToRight == 1) {
              x2r = x2 - d;
            }
            else {
              x2r = x2 + d;
            }


            // Check that the pixel is inside the image
            if (x2 >= 0 && x2 < (int)width && x2r >= 0 && x2r < (int)width && y2 >= 0 && y2 < (int)height) {
              sum += (image[y2 * width + x2] - avg) * (image2[y2 * width + x2r] - avg2);

              //pixel_left = (image[y2*width + x2] - mean_l);
						  //pixel_right = (image2[y2*width + (x2-d)] - mean_r);
						  //N += (pixel_left * pixel_right);
						  //std_r += (pixel_right * pixel_right);

              count++;
            }
          }
        }

        //std_r = sqrt(std_r);
        //float new_zncc = (N / (std*std_r));

        /* (new_zncc > zncc)
				{
					zncc = new_zncc;
					imageCopy[y*width + x] = (255*abs(float(d))/dispRange);
				}
        */
        float znccVal = sum / (std * std2);
        
        
        if (znccVal > zncc) {
          zncc = znccVal;
          imageCopy[y * width + x] = (255*abs(d))/dispRange;
        }
      }
      // Set the pixel value
      //imageCopy[y * width + x] = znccValInt;
    }
  }

  // Copy the image back
  memcpy(imageOut, imageCopy, sizeof(unsigned char) * width * height);

  // Free the memory
  free(imageCopy);
}

