#include "opencl_base.h"

OCL_Base::OCL_Base()
{
    init();
}

OCL_Base::~OCL_Base()
{
    status = clReleaseCommandQueue(commandQueue); //Release  Command queue.
	status = clReleaseContext(context); //Release context.

    if (devices != NULL)
	{
		free(devices);
		devices = NULL;
	}
}

void OCL_Base::init()
{
	/*Step1: Getting platforms and choose an available one.*/
    status = clGetPlatformIDs(0, NULL, &numPlatforms);
	if (status != CL_SUCCESS)
	{
		std::cout << "Error: Getting platforms!" << std::endl;
	}

	/*For clarity, choose the first available platform. */
	if (numPlatforms > 0)
	{
		platforms = (cl_platform_id*)malloc(numPlatforms * sizeof(cl_platform_id));
		status = clGetPlatformIDs(numPlatforms, platforms, NULL);
		platform = platforms[0];
		free(platforms);
	}

	/*Step 2:Query the platform and choose the first GPU device if has one.Otherwise use the CPU as device.*/
	status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
	if (numDevices == 0) //no GPU available.
	{
		std::cout << "No GPU device available." << std::endl;
		std::cout << "Choose CPU as default device." << std::endl;
		status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 0, NULL, &numDevices);
		devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
		status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, numDevices, devices, NULL);
	}
	else
	{
		devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
		status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, numDevices, devices, NULL);
	}

	/*Step 3: Create context.*/
	context = clCreateContext(NULL, 1, devices, NULL, NULL, NULL);

	/*Step 4: Creating command queue associate with the context.*/
	commandQueue = clCreateCommandQueue(context, devices[0], 0, NULL);

}
